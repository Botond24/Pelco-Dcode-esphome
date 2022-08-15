#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "libraries/PelcoDProtocolParser/PelcoDProtocolParser.h"




class epshome::PelcoDcode : public esphome::Component /*public esphome::UARTComponent*/ {
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
        map <String, pelco::PelcoDCommands> command_map_{
            //BASIC COMMANDS
            {"CAMERA_ON",pelco::PelcoDCommands::CAMERA_ON},
            {"CAMERA_OFF",pelco::PelcoDCommands::CAMERA_OFF},
            {"IRIS_OPEN",pelco::PelcoDCommands::IRIS_OPEN},
            {"IRIS_CLOSE",pelco::PelcoDCommands::IRIS_CLOSE},
            {"UP",pelco::PelcoDCommands::UP},
            {"DOWN",pelco::PelcoDCommands::DOWN},
            {"LEFT",pelco::PelcoDCommands::LEFT},
            {"RIGHT",pelco::PelcoDCommands::RIGHT},
            {"UP_LEFT",pelco::PelcoDCommands::UP_LEFT},
            {"UP_RIGHT",pelco::PelcoDCommands::UP_RIGHT},
            {"DOWN_LEFT",pelco::PelcoDCommands::DOWN_LEFT},
            {"DOWN_RIGHT",pelco::PelcoDCommands::DOWN_RIGHT},
            {"STOP",pelco::PelcoDCommands::STOP},
            {"ZOOM_WIDE",pelco::PelcoDCommands::ZOOM_WIDE},
            {"ZOOM_TELE",pelco::PelcoDCommands::ZOOM_TELE},
            {"ZOOM_STOP",pelco::PelcoDCommands::ZOOM_STOP},
            {"FOCUS_NEAR",pelco::PelcoDCommands::FOCUS_NEAR},
            {"FOCUS_FAR",pelco::PelcoDCommands::FOCUS_FAR},
            {"FOCUS_STOP",pelco::PelcoDCommands::FOCUS_STOP},
            {"FOCUS_NEAR",pelco::PelcoDCommands::FOCUS_NEAR},
            {"FOCUS_FAR",pelco::PelcoDCommands::FOCUS_FAR},
            {"FOCUS_STOP",pelco::PelcoDCommands::FOCUS_STOP},
            //EXTENDED COMMANDS
            {"SET_PRESET",pelco::PelcoDCommands::SET_PRESET},
            {"CLEAR_PRESET",pelco::PelcoDCommands::CLEAR_PRESET},
            {"GO_TO_PRESET",pelco::PelcoDCommands::GO_TO_PRESET},
            {"FLIP_180DEG_ABOUT",pelco::PelcoDCommands::FLIP_180DEG_ABOUT},
            {"GO_TO_ZERO_PAN",pelco::PelcoDCommands::GO_TO_ZERO_PAN},
            {"SET_AUXILIARY",pelco::PelcoDCommands::SET_AUXILIARY},
            {"CLEAR_AUXILIARY",pelco::PelcoDCommands::CLEAR_AUXILIARY},
            {"REMOTE_RESET",pelco::PelcoDCommands::REMOTE_RESET},
            {"SET_ZONE_START",pelco::PelcoDCommands::SET_ZONE_START},
            {"SET_ZONE_END",pelco::PelcoDCommands::SET_ZONE_END},
            {"WRITE_CHAR_TO_SCREEN",pelco::PelcoDCommands::WRITE_CHAR_TO_SCREEN},
            {"CLEAR_SCREEN",pelco::PelcoDCommands::CLEAR_SCREEN},
            {"ALARM_ACKNOWLEDGE",pelco::PelcoDCommands::ALARM_ACKNOWLEDGE},
            {"ZONE_SCAN_ON",pelco::PelcoDCommands::ZONE_SCAN_ON},
            {"ZONE_SCAN_OFF",pelco::PelcoDCommands::ZONE_SCAN_OFF},
            {"SET_PATTERN_START",pelco::PelcoDCommands::SET_PATTERN_START},
            {"SET_PATTERN_STOP",pelco::PelcoDCommands::SET_PATTERN_STOP},
            {"RUN_PATTERN",pelco::PelcoDCommands::RUN_PATTERN},
            {"SET_ZOOM_SPEED",pelco::PelcoDCommands::SET_ZOOM_SPEED},
            {"SET_FOCUS_SPEED",pelco::PelcoDCommands::SET_FOCUS_SPEED},
            {"RESET_CAMERA_TO_DEFAULT",pelco::PelcoDCommands::RESET_CAMERA_TO_DEFAULT},
            {"AUTO_FOCUS_AUTO_ON_OFF",pelco::PelcoDCommands::AUTO_FOCUS_AUTO_ON_OFF},
            {"AUTO_IRIS_AUTO_ON_OFF",pelco::PelcoDCommands::AUTO_IRIS_AUTO_ON_OFF},
            {"AGC_AUTO_ON_OFF",pelco::PelcoDCommands::AGC_AUTO_ON_OFF},
            {"BACKLIGHT_COMPENSATION_ON_OFF",pelco::PelcoDCommands::BACKLIGHT_COMPENSATION_ON_OFF},
            {"AUTO_WHITE_BALANCE_ON_OFF",pelco::PelcoDCommands::AUTO_WHITE_BALANCE_ON_OFF},
            {"ENABLE_DEVICE_PHASE_DELAY_MODE",pelco::PelcoDCommands::ENABLE_DEVICE_PHASE_DELAY_MODE},
            {"SET_SHUTTER_SPEED",pelco::PelcoDCommands::SET_SHUTTER_SPEED},
            {"ADJUST_LINE_LOCK_PHASE_DELAY",pelco::PelcoDCommands::ADJUST_LINE_LOCK_PHASE_DELAY},
            {"ADJUST_WHITE_BALANCE_R_B",pelco::PelcoDCommands::ADJUST_WHITE_BALANCE_R_B},
            {"ADJUST_WHITE_BALANCE_M_G",pelco::PelcoDCommands::ADJUST_WHITE_BALANCE_M_G},
            {"ADJUST_GAIN",pelco::PelcoDCommands::ADJUST_GAIN},
            {"ADJUST_AUTO_IRIS_LEVEL",pelco::PelcoDCommands::ADJUST_AUTO_IRIS_LEVEL},
            {"ADJUST_AUTO_IRIS_PEACK_VALUE",pelco::PelcoDCommands::ADJUST_AUTO_IRIS_PEACK_VALUE},
            {"QUERY",pelco::PelcoDCommands::QUERY}

        };
       
};
