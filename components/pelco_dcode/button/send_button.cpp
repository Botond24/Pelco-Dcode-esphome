#include "send_button.h"

namespace esphome {
namespace pelco {

void SendButton::press_action() { this->parent_->send(); }

}  // namespace pelco
}  // namespace esphome
