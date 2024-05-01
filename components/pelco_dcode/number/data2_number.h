#pragma once

#include "esphome/components/number/number.h"
#include "../pelco_dcode.h"

namespace esphome {
namespace pelco {

class Data2Number : public number::Number, public Parented<PelcoDcode> {
 public:
  Data2Number() = default;

 protected:
  void control(float value) override;
};

}  // namespace pelco
}  // namespace esphome
