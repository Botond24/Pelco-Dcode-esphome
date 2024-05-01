#include "data1_number.h"

namespace esphome {
namespace pelco {

void Data1Number::control(float value) {
  this->publish_state(value);
  this->parent_->set_data1(static_cast<uint8_t>(value));
}

}  // namespace pelco
}  // namespace esphome
