/**
 * @file mesh_data.hh
 * @author Carlo Musolino (musolino@itp.uni-frankfurt.de)
 * @brief 
 * @date 2024-10-09
 * 
 * @copyright This file is part of AVT
 * Copyright (C) 2023 Carlo Musolino
 *                                    
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *   
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 */
#ifndef MESH_DATA_HH__
#define MESH_DATA_HH__

#include <vt/transport.h>
#include <avt/mesh_array.hh>

#define DBG_ASSERT_BNDCHECK

namespace advect_1d {

/**
 * @brief A field on the grid, a series of mesh arrays representing 
 *        data, past timelevel, rhs.
 * 
 * @tparam have_rhs Whether the field is evolved.
 */
template<bool have_rhs> 
struct mesh_data_t { 
    private: 
    std::size_t npoints ;
    std::vector<mesh_array_t<double>> data ;
    mesh_array_t<double> rhs_data    ;

    public:
    /**
     * @brief Default ctor
     * data objects are initialised to nullptr's 
     */
    mesh_data_t(): 
    npoints(0), data(), 
    rhs_data() 
    { } ;

    mesh_data_t(std::size_t npoints__, std::size_t ntls_) : 
    npoints(npoints__)
    {
        for(std::size_t ii=0; ii<ntls_; ++ii)
            data.emplace_back( npoints ) ;

        if( have_rhs )
            rhs_data = mesh_array_t<double>(npoints) ;
    }

    double& operator() (std::size_t idx) { 
        #ifdef DBG_ASSERT_BNDCHECK
        assert(idx < npoints) ;
        #endif 
        return data[0](idx) ;     
    }

    mesh_array_t<double>& operator[](std::size_t tl_idx_) { 
        #ifdef DBG_ASSERT_BNDCHECK
        assert(tl_idx_ < data.size()) ;
        #endif 
        return data[tl_idx_] ; 
    }

    double& rhs(std::size_t idx) { 
        static_assert(have_rhs,
        "Trying to access rhs of non-evolved variable!\n") ;
        #ifdef DBG_ASSERT_BNDCHECK
        assert(idx < npoints) ;
        #endif 
        return rhs_data(idx); 
    }

    std::size_t size() { return npoints ; }

    std::size_t get_n_timelevels() { return data.size() ; }

    void rotate_timelevels() {
        // this is implemented in a 
        // clever way under the hood
        if( data.size() == 0 )
            return ;
        
        for( int ii=0; ii< data.size(); ii++ )
            data[ii+1] = data[ii] ;
    }

    mesh_data_t<have_rhs>& operator=(const mesh_data_t<have_rhs>& rhs_ ) {
        if( this == &rhs_ ){
            return *this ;
        }

        data.clear() ;
        for( int ii=0; ii<rhs_.data.size(); ++ii )
            data.push_back(rhs_.data[ii]) ;

        if( have_rhs )
            rhs_data = rhs_.rhs_data ;
        
        return *this ;
    }

    template< typename Serializer >
    void serialize( Serializer& s ) {
        s | have_rhs ;
        s | npoints ;
        s | data ;
        if( have_rhs )
            s | rhs_data ;
    }
};

using evolved_field_t = mesh_data_t<true> ;
using aux_field_t = mesh_data_t<false> ;

}

#endif