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

int __attribute__((weak)) getAnalogReadMaximum()
{
    return 1024;
}

/* GUVA_S12SD
Parameters: channel - the (analog) pin used to get output value of the sensor,
referenceVoltage - the reference voltage for the board e.g., 3.3v, 5.0v (DEFAULT). */
GUVA_S12SD::GUVA_S12SD(int channel, float referenceVoltage)
{
    this->channel = channel;
    this->referenceVoltageMv = referenceVoltage * 1000;
}

/* GUVA_S12SD_BEGIN
Prepares the sensor channel for use.
*/
void GUVA_S12SD::begin()
{
    pinMode(channel, INPUT);
    mvOut = -1;         
    level = -1;        
    index = -1;  
}

/* GUVA_S12SD_READ_OUTPUT_VOLTAGE
Returns the voltage (mV) measured by the sensor.
*/
float GUVA_S12SD::readOutputVoltageMv()
{
    return analogRead(channel) * referenceVoltageMv / getAnalogReadMaximum();
}

/* GUVA_S12SD_READ_OUTPUT_VOLTAGE
Returns the voltage (mV) measured by the sensor.
*/
float GUVA_S12SD::readOutputVoltage() // for backward compability only!
{
    return readOutputVoltageMv();
}

/* GUVA_S12SD_READ_AVG_OUTPUT_VOLTAGE
Returns the voltage (mV) measured by the sensor.
*/
float GUVA_S12SD::readAvgOutputVoltageMv(int count, int delayMs)
{
    int sensor_value = 0;
    int sensor_value_sum = 0;
    float vout = 0;

    for (int i = 0; i < count; i++)
    {
        sensor_value = analogRead(channel);
        sensor_value_sum = sensor_value + sensor_value_sum;
        if (delayMs > 0)
            delay(delayMs);
    }
    sensor_value = count == 1024 ? sensor_value_sum >> 10 : sensor_value / count;
    vout = sensor_value * referenceVoltageMv / getAnalogReadMaximum();
    return vout;
}

/* GUVA_S12SD_UV_INDEX
Function to convert sensor output voltage (mV) to UV index
for a GUVA-S12D based analog UV sensor based on a conversion table.
See http://www.esp32learning.com/code/esp32-and-guva-s12sd-uv-sensor-example.php
for conversion table ...
*/
float GUVA_S12SD::getUvIndex(float mV)
{
    const float mv_uvi[12] = {50, 227, 318, 408, 503, 606, 696, 795, 881, 976, 1079, 1170};
    int i = 0;
    float uvi = 0;
    for (i = 0; i < 12; i++)
    {
        if (mV < mv_uvi[i])
            break;
    }
    if (i < 11)
    {
        uvi = mV / mv_uvi[i] * (i + 1);
    }
    else
    {
        uvi = 11;
    }

    return uvi;
}

/* GUVA_S12SD_UV_LEVEL
Function to convert sensor output voltage (mV) to mW/m^2
for a GUVA-S12D based analog UV sensor: "The output voltage is: Vo = 4.3 * Diode-Current-in-uA.
So if the photocurrent is 1uA (9 mW/cm^2), the output voltage is 4.3V."
*/
float GUVA_S12SD::getUvLevel(float mV)
{
    float uv_level = mV / 43 * 9; // 1 uA per 9 mW/cm^2 at 4.3V
    return uv_level;
}

/* GUVA_S12SD_READ_SENSOR
Reads the sensor.
*/
void GUVA_S12SD::readSensor()
{
    mvOut = readAvgOutputVoltageMv();
    index = getUvIndex(mvOut);
    level = getUvLevel(mvOut);
}

/* GUVA_S12SD_GET_OUTPUT_VOLTAGE
Returns the output voltage.
*/
float GUVA_S12SD::getOutputVoltageMv()
{
    return mvOut;
}

/* GUVA_S12SD_GET_UV_INDEX
Returns the UV index.
*/
float GUVA_S12SD::getUvIndex()
{
    return index;
}

/* GUVA_S12SD_GET_UV_INDEX
Returns the UV level.
*/
float GUVA_S12SD::getUvLevel()
{
    return level;
}
