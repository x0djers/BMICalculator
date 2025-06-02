#include "../converter.h"

const UnitType Metre = {
    .name = "m",
    .system = "metric",
    .category = UNIT_LENGTH,
    .transferRate = 1,
};

const UnitType Centimeter = {
    .name = "cm",
    .system = "metric",
    .category = UNIT_LENGTH,
    .transferRate = 0.01,
};

const UnitType Kilo = {
    .name = "kg",
    .system = "metric",
    .category = UNIT_WEIGHT,
    .transferRate = 1,
};

