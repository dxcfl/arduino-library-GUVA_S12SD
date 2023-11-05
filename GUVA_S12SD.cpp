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

#include "Arduino.h"
#include "GUVA_S12SD.h"


/* GUVA_S12SD
Parameters: channel - the (analog) pin used to get output value of the sensor, 
supplyVoltage - the supply voltage of the sensor (5.0 volts DEFAULT or 3.3v volts). */
GUVA_S12SD::GUVA_S12SD(int channel, float supplyVoltage)
{
    this->channel = channel;
    this->supplyVoltage = supplyVoltage;
}

/* GUVA_S12SD_BEGIN
Prepares the sensor channel for use.
*/
void GUVA_S12SD::begin()
{
    pinMode(channel, INPUT);
    analogReadResolution(10);
    analogReference(INTERNAL);
}

/* GUVA_S12SD_READ_OUTPUT_VOLTAGE
Returns the voltage (mV) measured by the sensor.
*/
float GUVA_S12SD::readOutputVoltage()
{
    int sensor_value = 0;
    int sensor_value_sum = 0;
    float vout = 0;

    for (int i = 0; i < 1024; i++)
    {
        sensor_value = analogRead(channel);
        sensor_value_sum = sensor_value + sensor_value_sum;
        delay(1);
    }
    sensor_value = sensor_value_sum >> 10;
    vout = sensor_value * supplyVoltage * 1000 / getAnalogReadMaximum();
    return vout;
}

/* GUVA_S12SD_UV_INDEX
Function to convert sensor output voltage (mV) to UV index
for a GUVA-S12D based analog UV sensor based on a conversion table.
See http://www.esp32learning.com/code/esp32-and-guva-s12sd-uv-sensor-example.php
for conversion table ...
*/
float GUVA_S12SD::getUvIndex(float vout)
{
    const float mv_uvi[12] = {50, 227, 318, 408, 503, 606, 696, 795, 881, 976, 1079, 1170};
    int i = 0;
    float uvi = 0;
    for (i = 0; i < 12; i++)
    {
        if (vout < mv_uvi[i])
            break;
    }
    if (i < 11)
    {
        uvi = vout / mv_uvi[i] * (i + 1);
    }
    else
    {
        uvi = 11;
    }

    return uvi;
}

/* GUVA_S12SD_GET_UV_INDEX
Returns the UV index for the sensor output voltage (mV).
*/
float GUVA_S12SD::getUvIndex()
{
    return getUvIndex(readOutputVoltage());
}
