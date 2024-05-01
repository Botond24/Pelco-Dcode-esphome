#include "pelco_select.h"

namespace esphome {
namespace pelco {

void ControlSelect::control(const std::string &value) {
  this->publish_state(value);
  auto index = this->index_of(value);
  if (index.has_value()) {
    this->parent_->set_selected_command(static_cast<PelcoCommand>(index.value()));
  }
}

}  // namespace pelco
}  // namespace esphome
