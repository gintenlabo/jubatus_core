// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2011 Preferred Networks and Nippon Telegraph and Telephone Corporation.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License version 2.1 as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#include "passive_aggressive_1.hpp"

#include <algorithm>
#include <string>

#include "../common/exception.hpp"

using std::string;
using std::min;

namespace jubatus {
namespace core {
namespace classifier {

passive_aggressive_1::passive_aggressive_1(storage_ptr storage)
    : linear_classifier(storage) {
}

passive_aggressive_1::passive_aggressive_1(
    const classifier_config& config,
    storage_ptr storage)
    : linear_classifier(storage),
      config_(config) {

  if (!(0.f < config.regularization_weight)) {
    throw JUBATUS_EXCEPTION(
        common::invalid_parameter("0.0 < regularization_weight"));
  }
}

void passive_aggressive_1::train(const common::sfv_t& sfv,
                                 const string& label) {
  check_touchable(label);

  string incorrect_label;
  float margin = calc_margin(sfv, label, incorrect_label);
  float loss = 1.f + margin;
  if (loss < 0.f) {
    storage_->register_label(label);
    return;
  }
  float sfv_norm = squared_norm(sfv);
  if (sfv_norm == 0.f) {
    storage_->register_label(label);
    return;
  }

  update_weight(
      sfv,
      min(config_.regularization_weight, loss / (2 * sfv_norm)),
      label,
      incorrect_label);
  touch(label);
}

string passive_aggressive_1::name() const {
  return string("passive_aggressive_1");
}

}  // namespace classifier
}  // namespace core
}  // namespace jubatus
