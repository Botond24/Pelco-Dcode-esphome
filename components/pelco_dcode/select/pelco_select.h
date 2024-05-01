#pragma once

#include "esphome/components/select/select.h"
#include "../pelco_dcode.h"

namespace esphome {
namespace pelco {

class ControlSelect : public select::Select, public Parented<PelcoDcode> {
 public:
  ControlSelect() = default;

 protected:
  void control(const std::string &value) override;
};

}  // namespace pelco
}  // namespace esphome
