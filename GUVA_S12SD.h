/*
GUVA_S12SD - Arduino Library for GUVA-S12SD UV Sensors
Copyright (C) 2023   dxcfl

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GUVA_S12SD_H
#define GUVA_S12SD_H

class GUVA_S12SD
{
public:
  GUVA_S12SD(int channel, float referenceVoltage = 5.0);
  void begin();
  float readOutputVoltage();   // mV (millivolts)
  float readOutputVoltageMv(); // mV (millivolts)
  float readAvgOutputVoltageMv(int count = 1024, int delayMs = 0);
  float getUvIndex(float mv); // 0 - 11
  float getUvLevel(float mv); // mW/m^2 (milliwatts per square meter)
  void readSensor();
  float getOutputVoltageMv(); // mV (millivolts)
  float getUvIndex();         // 0 - 11
  float getUvLevel();         // mW/m^2 (milliwatts per square meter)

private:
  int channel;
  float referenceVoltageMv; // mV (millivolts)
  float mvOut = -1;         // mV (millivolts)
  float level = -1;         // mW/m^2 (milliwatts per square meter)
  float index = -1;         // 0 - 11
};

#endif
