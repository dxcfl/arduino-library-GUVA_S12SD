// Example testing sketch for the GUVA-S12SD UV sensor
// Written by dxcfl, public domain

// REQUIRES the following Arduino library:
// - GUVA-S12SD UV Sensor Library: https://github.com/dxcfl/arduino-library-GUVA_S12SD
#include "GUVA_S12SD.h"

#define GUVA_S12SD_PIN 0       // Analog pin connected to the UV sensor
#define GUVA_S12SD_VOLTAGE 5.0  // Supply voltage for the UV sensor (usually same as board supply voltage)

// Initialize UV sensor.

GUVA_S12SD guva_s12sd(GUVA_S12SD_PIN, GUVA_S12SD_VOLTAGE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("GUVA-S12SD test!"));

  guva_s12sd.begin();
}

void loop() {

  float uv_index;
  float vout;

  // Read the output voltage (mV) from the sensor
  vout =  guva_s12sd.readOutputVoltage(); 
  
  // Calculate the UV index based on the sensor's output voltage
  uv_index = guva_s12sd.getUvIndex(vout); 

  Serial.print(F("Sensor GUVA-S12D - Voltage: "));
  Serial.print(vout);
  Serial.println(F(" mV"));
  Serial.print(F("Sensor GUVA-S12D - UV index: "));
  Serial.println(uv_index);
  Serial.println(F("- - - - - - - - - - - - - - - - - - - - - - - - "));
 
  // Wait a few seconds between measurements.
  delay(2000);
}
