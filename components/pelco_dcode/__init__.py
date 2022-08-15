import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ["uart"]
ADDRESS = "address"

pelco_dcode = cg.register_component("pelco_dcode", cg.Component)

CONFIG_SCHEMA = (
	cv.Schema(
		{
			cv.GenerateID(): cv.declare_id(pelco_dcode),
			cv.Required(CONF_UART_ID): cv.use_id(uart.UARTDevice),
			cv.Optional(ADDRESS, default=1): cv.int_range(1, 255),
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