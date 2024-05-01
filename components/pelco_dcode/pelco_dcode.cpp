#include "pelco_dcode.h"

static const char *TAG = "pelcodcode";


namespace esphome {
namespace pelco {

void PelcoDcode::setup() {
  ESP_LOGCONFIG(TAG, "Pelco-Dcode starting...");
  set_parity(esphome::uart::UARTParityOptions::UART_CONFIG_PARITY_NONE);
  set_data_bits(8);
  set_stop_bits(1);
}

void PelcoDcode::loop() {}

void PelcoDcode::dump_config() {
  ESP_LOGCONFIG(TAG, "Pelco-Dcode:");
  LOG_PIN("  Flow Control Pin: ", this->flow_control_pin_);
}

void PelcoDcode::GetChecksum(uint8_t *packet) {
  /*uint32_t checksum =
      (uint32_t) packet[1] + (uint32_t) packet[2] + (uint32_t) packet[3] + (uint32_t) packet[4] + (uint32_t) packet[5];
  checksum %= 0x100;*/
  uint8_t checksum = packet[1]+packet[5];

  packet[6] = (uint8_t) checksum;
}

void PelcoDcode::send() {
  uint8_t packet[7];
  if (!GetCommand(packet,address_,selected_command_,data1_,data2_)) {
    ESP_LOGE(TAG, "wrong command: %u (%x)",selected_command_,selected_command_);
    return;
  }
  if (flow_control_pin_ != nullptr)
    flow_control_pin_->digital_write(true);
  send_raw(packet);
  if (flow_control_pin_ != nullptr)
    flow_control_pin_->digital_write(false);
}
void PelcoDcode::send_raw(const uint8_t *payload) {
  write_array(payload,7);
}


bool PelcoDcode::GetCommand(uint8_t *packet, uint8_t address, PelcoCommand command_ID, uint8_t data_1, uint8_t data_2) {
  packet[0] = 0xFF;
  packet[1] = address;
  // Check command.
  switch (command_ID) {
    case PelcoCommands::CAMERA_ON:
      packet[2] = 0x0A;
      packet[3] = 0x00;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::CAMERA_OFF:
      packet[2] = 0x02;
      packet[3] = 0x00;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::IRIS_CLOSE:
      packet[2] = 0x08;
      packet[3] = 0x00;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::IRIS_OPEN:
      packet[2] = 0x0A;
      packet[3] = 0x00;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::FOCUS_NEAR:
      packet[2] = 0x09;
      packet[3] = 0x00;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::FOCUS_FAR:
      packet[2] = 0x08;
      packet[3] = 0x80;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::FOCUS_STOP:
      packet[2] = 0x08;
      packet[3] = 0x00;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ZOOM_WIDE:
      packet[2] = 0x08;
      packet[3] = 0x40;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ZOOM_TELE:
      packet[2] = 0x08;
      packet[3] = 0x20;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ZOOM_STOP:
      packet[2] = 0x08;
      packet[3] = 0x00;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::DOWN:
      packet[2] = 0x08;
      packet[3] = 0x10;
      packet[4] = 0x00;
      packet[5] = data_2;
      GetChecksum(packet);
      return true;

    case PelcoCommands::UP:
      packet[2] = 0x08;
      packet[3] = 0x08;
      packet[4] = 0x00;
      packet[5] = data_2;
      GetChecksum(packet);
      return true;

    case PelcoCommands::LEFT:
      packet[2] = 0x08;
      packet[3] = 0x04;
      packet[4] = data_1;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::RIGHT:
      packet[2] = 0x08;
      packet[3] = 0x02;
      packet[4] = data_1;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::UP_RIGHT:
      packet[2] = 0x08;
      packet[3] = 0x0A;
      packet[4] = data_1;
      packet[5] = data_2;
      GetChecksum(packet);
      return true;

    case PelcoCommands::UP_LEFT:
      packet[2] = 0x08;
      packet[3] = 0x0C;
      packet[4] = data_1;
      packet[5] = data_2;
      GetChecksum(packet);
      return true;

    case PelcoCommands::DOWN_RIGHT:
      packet[2] = 0x08;
      packet[3] = 0x12;
      packet[4] = data_1;
      packet[5] = data_2;
      GetChecksum(packet);
      return true;

    case PelcoCommands::DOWN_LEFT:
      packet[2] = 0x08;
      packet[3] = 0x14;
      packet[4] = data_1;
      packet[5] = data_2;
      GetChecksum(packet);
      return true;

    case PelcoCommands::STOP:
      packet[2] = 0x08;
      packet[3] = 0x00;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::SET_PRESET:
      packet[2] = 0x00;
      packet[3] = 0x03;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::CLEAR_PRESET:
      packet[2] = 0x00;
      packet[3] = 0x05;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::GO_TO_PRESET:
      packet[2] = 0x00;
      packet[3] = 0x07;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::FLIP_180DEG_ABOUT:
      packet[2] = 0x00;
      packet[3] = 0x07;
      packet[4] = 0x00;
      packet[5] = 0x21;
      GetChecksum(packet);
      return true;

    case PelcoCommands::GO_TO_ZERO_PAN:
      packet[2] = 0x00;
      packet[3] = 0x07;
      packet[4] = 0x00;
      packet[5] = 0x22;
      GetChecksum(packet);
      return true;

    case PelcoCommands::SET_AUXILIARY:
      packet[2] = 0x00;
      packet[3] = 0x09;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::CLEAR_AUXILIARY:
      packet[2] = 0x00;
      packet[3] = 0x0B;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::REMOTE_RESET:
      packet[2] = 0x00;
      packet[3] = 0x0F;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::SET_ZONE_START:
      packet[2] = 0x00;
      packet[3] = 0x11;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::SET_ZONE_END:
      packet[2] = 0x00;
      packet[3] = 0x13;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::WRITE_CHAR_TO_SCREEN:
      packet[2] = 0x00;
      packet[3] = 0x15;
      packet[4] = data_1;
      packet[5] = data_2;
      GetChecksum(packet);
      return true;

    case PelcoCommands::CLEAR_SCREEN:
      packet[2] = 0x00;
      packet[3] = 0x17;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ALARM_ACKNOWLEDGE:
      packet[2] = 0x00;
      packet[3] = 0x19;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ZONE_SCAN_ON:
      packet[2] = 0x00;
      packet[3] = 0x1B;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ZONE_SCAN_OFF:
      packet[2] = 0x00;
      packet[3] = 0x1D;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::SET_PATTERN_START:
      packet[2] = 0x00;
      packet[3] = 0x1F;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::SET_PATTERN_STOP:
      packet[2] = 0x00;
      packet[3] = 0x21;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::RUN_PATTERN:
      packet[2] = 0x00;
      packet[3] = 0x23;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::SET_ZOOM_SPEED:
      packet[2] = 0x00;
      packet[3] = 0x25;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::SET_FOCUS_SPEED:
      packet[2] = 0x00;
      packet[3] = 0x27;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::RESET_CAMERA_TO_DEFAULT:
      packet[2] = 0x00;
      packet[3] = 0x29;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::AUTO_FOCUS_AUTO_ON_OFF:
      packet[2] = 0x00;
      packet[3] = 0x2B;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::AUTO_IRIS_AUTO_ON_OFF:
      packet[2] = 0x00;
      packet[3] = 0x2D;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::AGC_AUTO_ON_OFF:
      packet[2] = 0x00;
      packet[3] = 0x2F;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::BACKLIGHT_COMPENSATION_ON_OFF:
      packet[2] = 0x00;
      packet[3] = 0x31;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::AUTO_WHITE_BALANCE_ON_OFF:
      packet[2] = 0x00;
      packet[3] = 0x33;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ENABLE_DEVICE_PHASE_DELAY_MODE:
      packet[2] = 0x00;
      packet[3] = 0x35;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::SET_SHUTTER_SPEED:
      packet[2] = 0x00;
      packet[3] = 0x37;
      packet[4] = 0x00;
      packet[5] = data_1;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ADJUST_LINE_LOCK_PHASE_DELAY:
      packet[2] = data_1;
      packet[3] = 0x39;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ADJUST_WHITE_BALANCE_R_B:
      packet[2] = data_1;
      packet[3] = 0x3B;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ADJUST_WHITE_BALANCE_M_G:
      packet[2] = data_1;
      packet[3] = 0x3D;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ADJUST_GAIN:
      packet[2] = data_1;
      packet[3] = 0x3F;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ADJUST_AUTO_IRIS_LEVEL:
      packet[2] = data_1;
      packet[3] = 0x41;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::ADJUST_AUTO_IRIS_PEACK_VALUE:
      packet[2] = data_1;
      packet[3] = 0x43;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    case PelcoCommands::QUERY:
      packet[2] = 0x00;
      packet[3] = 0x45;
      packet[4] = 0x00;
      packet[5] = 0x00;
      GetChecksum(packet);
      return true;

    default:
      return false;
  }
}
};
};
// TODO: Implement Recieve as of https://asset.fujifilm.com/www/mx/files/2022-11/e3b519d711774a7f62281f930156379a/pelco-d_protocol_specification_for_sx800-801_v2.00.4_eng.pdf