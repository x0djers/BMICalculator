#ifndef CONVERTER_H
#define CONVERTER_H

/**
  @enum UnitCategory
  @brief Categories of physical units for grouping and conversion.
*/
typedef enum {
    UNIT_LENGTH, ///< Units measuring length or distance
    UNIT_WEIGHT,   ///< Units measuring mass or weight
} UnitCategory;

/**
  @struct UnitType
  @brief The structure of the unit of measurement.
*/
typedef struct {
    char* name;            ///< Unit name in the lower register.
    char* system;          ///< The name of the measurement system.
    UnitCategory category;  ///< Classification category for this unit.
    double transferRate;   ///< Translation coefficient to the SI system.
} UnitType;

/*
  @struct MeasuredValue
  @brief Abstract structure for storing values with units of measurement.
*/
typedef struct {
    float value;           ///< The value of the parameter.
    UnitType unit;         ///< The unit of measurement of the parameter.
} MeasuredValue;

// Announcement of units of the metric system
extern const UnitType Metre;
extern const UnitType Centimeter;
extern const UnitType Kilo;

// Announcement of units of the imperial system
extern const UnitType Inch;
extern const UnitType Pound;

MeasuredValue convertToSI(const MeasuredValue inputValue);

#endif
