import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import (
    ENTITY_CATEGORY_CONFIG,
)
from .. import CONF_PELCO_ID, PelcoComponent, pelco_ns

SendButton = pelco_ns.class_("SendButton", button.Button)

CONF_SEND = "send"
DEVICE_CLASS_BUTTON = "button"

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_PELCO_ID): cv.use_id(PelcoComponent),
    cv.Optional(CONF_SEND): button.button_schema(
        SendButton,
        device_class=DEVICE_CLASS_BUTTON,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon="mdi:send",
    ),
}


async def to_code(config):
    pelco_component = await cg.get_variable(config[CONF_PELCO_ID])
    if send_config := config.get(CONF_SEND):
        b = await button.new_button(send_config)
        await cg.register_parented(b, config[CONF_PELCO_ID])
        cg.add(pelco_component.set_restart_button(b))
