#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif
#ifdef USE_BUTTON
#include "esphome/components/button/button.h"
#endif
#ifdef USE_SELECT
#include "esphome/components/select/select.h"
#endif


namespace esphome {
namespace pelco {

enum PelcoCommand : uint8_t {
  // Main commands.
  CAMERA_ON,
  CAMERA_OFF,
  IRIS_CLOSE,
  IRIS_OPEN,
  FOCUS_NEAR,
  FOCUS_FAR,
  FOCUS_STOP,
  ZOOM_WIDE,
  ZOOM_TELE,
  ZOOM_STOP,
  DOWN,
  UP,
  LEFT,
  RIGHT,
  UP_RIGHT,
  UP_LEFT,
  DOWN_RIGHT,
  DOWN_LEFT,
  STOP,

  // Extended commands.
  SET_PRESET,
  CLEAR_PRESET,
  GO_TO_PRESET,
  FLIP_180DEG_ABOUT,
  GO_TO_ZERO_PAN,
  SET_AUXILIARY,
  CLEAR_AUXILIARY,
  REMOTE_RESET,
  SET_ZONE_START,
  SET_ZONE_END,
  WRITE_CHAR_TO_SCREEN,
  CLEAR_SCREEN,
  ALARM_ACKNOWLEDGE,
  ZONE_SCAN_ON,
  ZONE_SCAN_OFF,
  SET_PATTERN_START,
  SET_PATTERN_STOP,
  RUN_PATTERN,
  SET_ZOOM_SPEED,
  SET_FOCUS_SPEED,
  RESET_CAMERA_TO_DEFAULT,
  AUTO_FOCUS_AUTO_ON_OFF,
  AUTO_IRIS_AUTO_ON_OFF,
  AGC_AUTO_ON_OFF,
  BACKLIGHT_COMPENSATION_ON_OFF,
  AUTO_WHITE_BALANCE_ON_OFF,
  ENABLE_DEVICE_PHASE_DELAY_MODE,
  SET_SHUTTER_SPEED,
  ADJUST_LINE_LOCK_PHASE_DELAY,
  ADJUST_WHITE_BALANCE_R_B,
  ADJUST_WHITE_BALANCE_M_G,
  ADJUST_GAIN,
  ADJUST_AUTO_IRIS_LEVEL,
  ADJUST_AUTO_IRIS_PEACK_VALUE,
  QUERY
};

class PelcoDcode : public uart::UARTDevice, public Component {
#ifdef USE_NUMBER
  SUB_NUMBER(data1)
  SUB_NUMBER(data2)
#endif
#ifdef USE_BUTTON
  SUB_BUTTON(send)
#endif
#ifdef USE_SELECT
  SUB_SELECT(control)
#endif

 public:
  PelcoDcode() = default;

  void setup() override;
  void loop() override;
  void dump_config() override;

  float get_setup_priority() const override { return setup_priority::BUS - 1.0f; }

  void send();
  void send_raw(const uint8_t *payload);

  void set_data1(uint8_t data1) { data1_ = data1; }
  void set_data2(uint8_t data2) { data2_ = data2; }
  void set_selected_command(PelcoCommand command) { selected_command_ = command; }

  void set_flow_control_pin(GPIOPin *flow_control_pin) { this->flow_control_pin_ = flow_control_pin; };
  void set_address(uint8_t address) { address_ = address; }

 protected:
  void GetChecksum(uint8_t *packet);
  bool GetCommand(uint8_t *packet, uint8_t address, PelcoCommand command_ID, uint8_t data_1, uint8_t data_2);
  GPIOPin *flow_control_pin_{nullptr};
  uint8_t address_ = 0x01;
  PelcoCommand selected_command_ = PelcoCommand::CAMERA_ON;
  uint8_t data1_ = 0x00;
  uint8_t data2_ = 0x00;
};
};
};
