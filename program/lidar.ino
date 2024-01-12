#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(20000);
}

void loop()
{
  Serial.print("Range : ");
  Serial.println(sensor.readRangeSingleMillimeters());
  if(sensor.timeoutOccurred())  Serial.println("TIMEOUT");
}
