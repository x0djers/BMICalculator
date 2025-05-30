#include "../units.h"

const UnitType Inch = {
    .name = "inch",
    .system = "imperial",
    .category = UNIT_LENGTH,
    .transferRate = 0.0254,
};

const UnitType Pound = {
    .name = "lbs",
    .system = "imperial",
    .category = UNIT_WEIGHT,
    .transferRate = 0.4535924,
};