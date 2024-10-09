/**
 * @file node.hh
 * @author  (musolino@itp.uni-frankfurt.de)
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
#ifndef NODE_T_HH
#define NODE_T_HH

#include <vt/transport.h>

namespace advect_1d {

  struct node_t {
    bool is_finished_ = false;
    struct work_finished_msg : vt::Message {};
    // this will be called once the time of the simulation reaches max_time
    void work_finished_cback_(work_finished_msg*) { is_finished_ = true; }
    // this will be called on the root node only
    bool is_work_finished() { return is_finished_; }
  };
  using node_proxy_t = vt::objgroup::proxy::Proxy<node_t>;

  bool is_work_done( vt::objgroup::proxy::Proxy<node_t> const& this_proxy ) {
    auto const this_node = vt::theContext()->getNode() ;
    return this_proxy[this_node].invoke<
    decltype(&node_t::is_work_finished),
    &node_t::is_work_finished
    > () ;
  }

}

#endif
