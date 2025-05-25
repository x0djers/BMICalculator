#include <stdlib.h>
#include <string.h>

#include "units.h"

UnitType getSIUnit(const UnitType inputUnit) {
    UnitType resultUnit;
    switch (inputUnit.category) {
        case (UNIT_LENGTH):
            resultUnit = Metre;
            break;
        case (UNIT_WEIGHT):
            resultUnit = Kilo;
            break;
    }

    return resultUnit;
}

MeasuredValue convertToSI(const MeasuredValue inputValue) {
    MeasuredValue result = inputValue;

    if (strcmp(inputValue.unit.system, "metric") < 0 ||
        strcmp(inputValue.unit.name, "m") < 0) {
        const UnitType siUnit = getSIUnit(inputValue.unit);
        result.value = result.value * inputValue.unit.transferRate;
        result.unit = siUnit;
    }

    return result;
}
