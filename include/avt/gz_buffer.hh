/**
 * @file gz_buffer.hh
 * @author  (musolino@itp.uni-frankfurt.de)
 * @brief 
 * @date 2024-10-09
 * 
 * @copyright This file is part of AVT.
 * GRACE is an evolution framework that uses Finite Volume
 * methods to simulate relativistic spacetimes and plasmas
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
#ifndef AVT_GZ_BUFFERS_HH__
#define AVT_GZ_BUFFERS_HH__

#include "mesh_array.hh"
#include "loop_utils.hh"

namespace advect_1d {

    struct gz_buffer_t {
        private: 
        static std::size_t gz_size_ ;

        mesh_array_t<double> gz_data_ ;
    }

}

#endif 