/**
 * @file mesh_array.hh
 * @author  (musolino@itp.uni-frankfurt.de)
 * @brief 
 * @date 2024-10-09
 * 
 * @copyright This file is part of AVT.
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

#ifndef AVT_MESH_ARRAY_HH__
#define AVT_MESH_ARRAY_HH__

#include <vt/transport.h>
#include <memory>

#define AVT_ASSERT_SIZE_CHECK__

namespace advect_1d {

/**
 * @brief Mesh array type, holds data living on a mesh.
 * 
 * The data is allocated / deallocated using vt's pool allocators.
 * 
 * @tparam T Type of data.
 */
template<typename T>
struct mesh_array_t {
    private:

    struct mesh_array_destructor {
        void operator()(T* buf){  
            fmt::print("Destructor called\n");
            if( buf != nullptr  )
                vt::thePool()->dealloc((void*) buf) ;
            }
    } ;

    using avt_unique_ptr = std::unique_ptr<T, mesh_array_destructor> ;
    std::size_t size_ ;

    avt_unique_ptr data_ ;

    public: 

    mesh_array_t(): size_(0), data_(nullptr)
    { } ;

    mesh_array_t(std::size_t size__ ): size_(size__) {
        fmt::print("Allocating buffer of size {}\n", size_) ;
        data_ = avt_unique_ptr( (T*) vt::thePool()->alloc(sizeof(T)*size_ )) ;
        //data_ = avt_unique_ptr( (T*) malloc(sizeof(T)*size_) ) ;
    }

    T& operator() (std::size_t idx) {
        #ifdef AVT_ASSERT_SIZE_CHECK__
        assert(idx < size_ ) ;
        #endif 
        return data_.get()[idx] ;
    }

    T const_access(std::size_t idx) const {
        #ifdef AVT_ASSERT_SIZE_CHECK__
        assert(idx < size_ ) ;
        #endif 
        return data_.get()[idx] ;
    }

    mesh_array_t<T>& operator=(mesh_array_t<T> const & rhs_ ){
        if( this == &rhs_ )
            return *this ;

        if ( this-> size_ != rhs_.size_ ) 
        {
            if( data_ != nullptr)
                data_.release() ;
            size_ = rhs_.size_ ;
            data_ = avt_unique_ptr( (T*) vt::thePool()->alloc(size_) ) ;
        }
        // copy data
        std::copy( rhs_.data_.get(), 
            rhs_.data_.get()+size_, 
            this->data_.get() );
        
        return *this ;
    }

    mesh_array_t(mesh_array_t<T>&& rhs_ ): size_(rhs_.size_) {
        data_ = std::move(rhs_.data_) ;
    }

    mesh_array_t(const mesh_array_t<T>& rhs_ ): size_(rhs_.size_) {
        data_ = avt_unique_ptr( (T*) vt::thePool()->alloc(size_) ) ;
        std::copy( rhs_.data_.get(), 
            rhs_.data_.get()+size_, 
            this->data_.get() ) ;
    }

    template< typename Serializer >
    void serialize(Serializer& s){
        s | size_ ;
        s | data_ ;
    }


    ~mesh_array_t() = default ;
};

}

#endif 