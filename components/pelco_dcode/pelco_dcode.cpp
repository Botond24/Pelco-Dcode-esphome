#include "PelcoDProtocolParser.cpp"
#include "PelcoDProtocolParser.h"
#include "Pelco_Dcode.h"
#include <map>


static const char *TAG = "pelcodcode";

namespace esphome {
    void PelcoDcode::setup() {
    ESP_LOGCONFIG(TAG, "Pelco-Dcode starting...");
        
    }
    void PelcoDcode::loop() {
        
    }

    void PelcoDcode::send_command(
        String command,
        int data_1 = 0,
        int data_2 = 0) {
            uint8_t packet[7];
            uint8_t address = this->address_;
            pelco::PelcoDCommands command_ID = this->command_map_[command];
            uint8_t d_1 = data_1;
            uint8_t d_2 = data_2;
            auto protocolparser = new pelco::PelcoDProtocolParser();
            protocolparser->GetCommand(&packet, address, command_ID, d_1, d_2);
            this->stream_->write_array(packet, 7);
            ESP_LOGD(TAG, "Pelco-Dcode: %s", command.c_str());
            ESP_LOGD(TAG, "  Packet: %u", packet);
    }

    void PelcoDcode::dump_config() {
        ESP_LOGCONFIG(TAG, "Pelco-Dcode:");
        ESP_LOGCONFIG(TAG, "  Address: %u", this->address_);
        ESP_LOGCONFIG(TAG, "  UART: %s", this->stream_->get_name().c_str());
    }
}