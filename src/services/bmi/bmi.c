#include <string.h>

#include "bmi.h"
#include "../../utils/units/units.h"

MeasuredValue createHeightValue(const float height,
                                const char* units) {
    UnitType unitType = strcmp(units, "metric") == 0 ? Centimeter : Inch;

    MeasuredValue heightValue = {
        .value = (float)height,
        .unit  = unitType,
    };

    heightValue = convertToSI(heightValue);

    return heightValue;
}

MeasuredValue createWeightValue(const float weight,
                                const char* units) {
    UnitType unitType = strcmp(units, "metric") == 0 ? Kilo : Pound;

    MeasuredValue weightValue = {
        .value = (float)weight,
        .unit  = unitType,
    };

    weightValue = convertToSI(weightValue);

    return weightValue;
}

float calculateBMI(const float height,
                   const float weight,
                   const char* units) {
    float bmi = 0.0f;

    MeasuredValue heigthSI = createHeightValue(height, units);
    MeasuredValue weigthSI = createWeightValue(weight, units);

    bmi = weigthSI.value / (heigthSI.value * heigthSI.value);

    return bmi;
}
