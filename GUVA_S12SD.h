/*
GUVA_S12SD - Arduino Library for GUVA-S12SD UV Sensors
Copyright (C) 2023  dxcfl

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
    GUVA_S12SD(int channel, float supplyVoltage = 5.0);
    void begin();
    float readOutputVoltage();
    float getUvIndex(float vout);
    float getUvIndex();
  private:
    int channel;
    float supplyVoltage;
};

#endif
