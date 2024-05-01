import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv
from esphome.const import (
    ENTITY_CATEGORY_CONFIG,
)
from .. import CONF_PELCO_ID, PelcoComponent, pelco_ns

Data1Number = pelco_ns.class_("Data1Number", number.Number)
Data2Number = pelco_ns.class_("Data2Number", number.Number)

CONF_DATA1 = "data1"
CONF_DATA2 = "data2"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_PELCO_ID): cv.use_id(PelcoComponent),
        cv.Optional(CONF_DATA1): number.number_schema(
            Data1Number,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:cog",
        ),
        cv.Optional(CONF_DATA2): number.number_schema(
            Data2Number,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:cog",
        ),
    }
)


async def to_code(config):
    pelco_component = await cg.get_variable(config[CONF_PELCO_ID])
    if data1_config := config.get(CONF_DATA1):
        n = await number.new_number(
            data1_config,
            min_value=0,
            max_value=255,
            step=1,
        )
        await cg.register_parented(n, pelco_component)
        cg.add(pelco_component.set_data1_number(n))
    if data2_config := config.get(CONF_DATA2):
        n = await number.new_number(
            data2_config,
            min_value=0,
            max_value=255,
            step=1,
        )
        await cg.register_parented(n, pelco_component)
        cg.add(pelco_component.set_data2_number(n))
