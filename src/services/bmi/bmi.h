#ifndef BMI_H
#define BMI_H

/**
  @brief Calculates the Body Mass Index (BMI) based on height and weight.

  Supports both metric and imperial measurement systems:
  - Metric: height in centimeters, weight in kilograms.
  - Imperial: height in inches, weight in pounds(lbs).

  @param height The person's height:
                - in centimeters if units == "metric"
                - in inches if units == "imperial"
  @param weight The person's weight:
                - in kilograms if units == "metric"
                - in pounds if units == "imperial"
  @param units A string specifying the measurement system:
               - "metric" for metric system
               - "imperial" for imperial system
  @return float The calculated BMI value.
*/
float calculateBMI(const float height,
                   const float weight,
                   const char* units);

#endif