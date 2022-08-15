#include "libraries\PelcoDProtocolParser\PelcoDProtocolParser.cpp"
#include "libraries\PelcoDProtocolParser\PelcoDProtocolParser.h"
#include "Pelco_Dcode.h"




namespace esphome {
    void PelcoDcode::setup() {
    auto uart = this->get_component<UARTComponent>();

        
    }
    void PelcoDcode::loop() {
        
    }

    void PelcoDcode::SendCommand(
        string command,
        int data_1 = 0,
        int data_2 = 0) {
            uint8_t packet[7];
            uint8_t address = this->address_;
            pelco::PelcoDCommands command_ID = this->command_map_[command];
            uint8_t d_1 = data_1;
            uint8_t d_2 = data_2;
            pelco::PelcoDProtocolParser::GetCommand(&packet, address, command_ID, d_1, d_2);
            this->stream_->write_array(packet, 7);
    }

    void PelcoDcode::dump_config() {
        ESP_LOGCONFIG(TAG, "Pelco-Dcode:");
        ESP_LOGCONFIG(TAG, "  Address: %u", this->address_);
        ESP_LOGCONFIG(TAG, "  UART: %s", this->stream_->get_name().c_str());
    }
}