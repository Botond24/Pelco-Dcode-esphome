#pragma once

#include "esphome/components/button/button.h"
#include "../pelco_dcode.h"

namespace esphome {
namespace pelco {

class SendButton : public button::Button, public Parented<PelcoDcode> {
 public:
  SendButton() = default;

 protected:
  void press_action() override;
};

}  // namespace pelco
}  // namespace esphome
