import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.cpp_helpers import gpio_pin_expression
from esphome.components import uart
from esphome.const import (
	CONF_FLOW_CONTROL_PIN,
	CONF_ID,
	CONF_ADDRESS,
)
from esphome import pins

DEPENDENCIES = ["uart"]

pelco_ns = cg.esphome_ns.namespace("pelco")
PelcoComponent = pelco_ns.class_("PelcoDcode", cg.Component, uart.UARTDevice)
MULTI_CONF = True

CONF_PELCO_ID = "pelco_id"

CONFIG_SCHEMA = (
	cv.Schema(
		{
			cv.GenerateID(): cv.declare_id(PelcoComponent),
			cv.Optional(CONF_FLOW_CONTROL_PIN): pins.gpio_output_pin_schema,
			cv.Optional(CONF_ADDRESS, default=1): cv.int_range(0, 255),
		}
	)
	.extend(cv.COMPONENT_SCHEMA)
	.extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
	cg.add_global(pelco_ns.using)
	var = cg.new_Pvariable(config[CONF_ID])
	await cg.register_component(var, config)

	await uart.register_uart_device(var, config)

	if CONF_FLOW_CONTROL_PIN in config:
		pin = await gpio_pin_expression(config[CONF_FLOW_CONTROL_PIN])
		cg.add(var.set_flow_control_pin(pin))
	cg.add(var.set_address(config[CONF_ADDRESS]))

