/**
 * @file loop_utils.hh
 * @author Carlo Musolino (musolino@itp.uni-frankfurt.de)
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
#ifndef LOOP_UTILS_HH__
#define LOOP_UTILS_HH__

#include<stdlib.h>

namespace advect_1d { namespace utils {

/**
 * @brief Call a lambda in a simd loop.
 * 
 * @tparam F Type of the lambda. 
 * @param lo_ Lower bound of iteration. 
 * @param hi_ Upper bound of iteration. 
 * @param func Loop body (lambda).
 */
template<typename F>
static inline __attribute__((always_inline)) 
void avt_simd_loop(std::size_t lo_, std::size_t hi_,
                    F&& func ) 
{
    #pragma omp simd
    for(std::size_t ii=lo_; ii<hi_; ++ii)
        func(ii) ; 
}

}
}

#endif