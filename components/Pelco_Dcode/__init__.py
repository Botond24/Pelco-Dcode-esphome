import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ["uart"]
ADDRESS = "address"

Pelco_Dcode = cg.register_component("Pelco_Dcode", cg.Component)

CONFIG_SCHEMA = (
	cv.Schema(
		{
			cv.GenerateID(): cv.declare_id(Pelco_Dcode),
			cv.Required(CONF_UART_ID): cv.use_id(uart.UARTDevice),
			cv.Optional(ADDRESS, default=0): cv.int_range(0, 255),
		}
	)
		.extend(cv.COMPONENT_SCHEMA)
		.extend(uart.UART_DEVICE_SCHEMA)
)

def to_code(config):
	var = cg.new_Pvariable(config[CONF_ID])
	cg.add(var.set_address(config[ADDRESS]))
	cg.add(var.set_uart(config[CONF_UART_ID]))

	yield cg.register_component(var, config)
	yield uart.register_uart_device(var, config)