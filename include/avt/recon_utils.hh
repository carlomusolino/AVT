/**
 * @file recon_utils.hh
 * @author Carlo Musolino (musolino@itp.uni-frankfurt.de)
 * @brief 
 * @date 2024-10-09
 * 
 * @copyright Copyright (C) 2023 Carlo Musolino
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
#ifndef FVCC_1D_REC_HELPERS_HH
#define FVCC_1D_REC_HELPERS_HH

#include <cmath>

namespace advect_1d {

  static inline constexpr int sign(const double& x){return (0 < x) - (x < 0);};

  static inline constexpr double max(const double& x, const double& y){ return (x>y) ? x : y;};
  
  template<typename... Targs>
  inline constexpr double max(const double& x, const double & y, Targs... Fargs)
  {
    return max(x,max(y,Fargs...));
  }
  
  
  inline constexpr double min(const double& x, const double& y){ return (x>y) ? y : x;};
  
  template<typename... Targs>
  inline constexpr double min(const double& x, const double & y, Targs... Fargs)
  {
    return min(x,min(y,Fargs...));
  }
  
  
  static inline double minmod(const double& x, const double& y){
    return 0.5*(sign(x)+sign(y))*min(std::fabs(x),std::fabs(y)) ;
  };
  
  static inline double mc2(const double& x, const double& y){
    return 0.5*(sign(x)+sign(y))*min(2.*std::fabs(x),2.*std::fabs(y), 0.5*std::fabs(x+y));};
  
}

#endif
