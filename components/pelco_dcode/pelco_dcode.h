#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "PelcoDProtocolParser.h"



namespace esphome {
class PelcoDcode : public Component /*public UARTComponent*/ {
    public:
        PelcoDcode() = default;
        /*Pelco_Dcode(esphome::UARTComponent *parent) : UARTComponent(parent) {}*/
        void set_uart_parent(esphome::uart::UARTComponent *parent) { this->stream_ = parent; }

        void setup() override;
        void loop() override;
        void dump_config() override;

        float get_setup_priority() const override { return esphome::setup_priority::AFTER_WIFI; }

        void set_address(uint8_t address) { this->address_ = address; }

        void send_command(string command, int data_1 = 0, int data_2 = 0);

    protected:
        esphome::uart::UARTComponent *stream_{nullptr};
        int address_{1};
        uint32_t baude_rate_{9600};
        uint8_t rx_pin_{0};
        uint8_t tx_pin_{};
        pelco::PelcoDProtocolParser parser_;
};
       
};
