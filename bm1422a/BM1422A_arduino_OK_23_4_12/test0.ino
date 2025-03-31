
//#include <BM1422AGMV.h>

/*****************************************************************************
  BM1422AGMV.ino

 Copyright (c) 2022 ROHM Co.,Ltd.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
******************************************************************************/
#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include "BM1422AGMV.h"

#define SYSTEM_BAUDRATE (115200)
#define DATA_DIGIT      (3)
#define ERROR_WAIT      (1000)
#define ERROR_POINT     (30)
#define WAIT_TIME       (100)

#define AXIS_X          (0)
#define AXIS_Y          (1)
#define AXIS_Z          (2)

BM1422AGMV bm1422a(BM1422AGMV_ADDR_LOW);
void wait_time(uint32_t delay_time);
void error_func(int32_t result);

void setup()
{
    int32_t result;
    float32 version;

    (void)Serial.begin(SYSTEM_BAUDRATE);
    while (!Serial) {
    }

    (void)Serial.println("BM1422AGMV Sample Code Version : 1.1");

    version = bm1422a.get_version();
    (void)Serial.print("BM1422AGMV Driver Version : ");
    (void)Serial.println(version, 1);

    Wire.begin();

    result = bm1422a.init();
  
    if (result == BM1422AGMV_OK) {
        (void)bm1422a.start();
    } else {
        error_func(result);
    }

    delay(BM1422AGMV_MEAS_TIME);

    return;
}

void loop() 
{
    int32_t result;
    int32_t wia;
    float32 mag[BM1422AGMV_DATA_SIZE];

        
    bm1422a.wia_read(0x0F, wia, 1);
    Serial.print(wia);        
    result = bm1422a.get_val(mag);
    if (result == BM1422AGMV_OK) {
        // (void)Serial.print("X : Y : Z [uT] = ");
        (void)Serial.print(mag[AXIS_X], DATA_DIGIT);
        (void)Serial.print(",");
        (void)Serial.print(mag[AXIS_Y], DATA_DIGIT);
        (void)Serial.print(",");
        (void)Serial.print(mag[AXIS_Z], DATA_DIGIT);
        (void)Serial.println();
    } else {
        error_func(result);
    }

    // For Single Measurement
    (void)bm1422a.start();

    wait_time(WAIT_TIME);

    return;
}

void wait_time(uint32_t delay_time)
{
    if (delay_time < BM1422AGMV_MEAS_TIME) {
        delay_time = BM1422AGMV_MEAS_TIME;
    }

    delay(delay_time);
    return;
}

void error_func(int32_t result)
{
    uint8_t cnt = 0;

    switch (result) {
        case BM1422AGMV_COMM_ERROR :
            (void)Serial.println("Communication Error.");
            break;

        case BM1422AGMV_WAI_ERROR :
            (void)Serial.println("Parameter Error.");
            break;

        default :
            (void)Serial.println("Unknown Error.");
            break;
    }

    (void)Serial.println("Check System and Driver Parameter.");
    while (1) {
        (void)Serial.print(".");
        if (cnt < ERROR_POINT) {
            cnt++;
        } else {
            cnt = 0;
            (void)Serial.println();
        }
        delay(ERROR_WAIT);
    }

    return;
}