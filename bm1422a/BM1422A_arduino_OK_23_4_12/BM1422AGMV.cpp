/*****************************************************************************
  BM1422AGMV.cpp

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
#include <Wire.h>
#include "BM1422AGMV.h"


BM1422AGMV::BM1422AGMV(bool addr_pin)
{
    if (addr_pin) {
        Address = BM1422AGMV_SLAVE_ADDRESS_0F;
    } else {
        Address = BM1422AGMV_SLAVE_ADDRESS_0E;
    }

    return;
}

BM1422AGMV::~BM1422AGMV()
{
    Address = 0;

    return;
}

int32_t BM1422AGMV::init(void)
{
    int32_t result;

    result = init_check_val();
    Serial.print("init_result:");
    Serial.println(result);
    if (result == BM1422AGMV_OK) {
        (void)init_setting_ic();
    }
    

    return result;
}

int32_t BM1422AGMV::start(void)
{
    int32_t result;
    uint8_t cntl1_val = BM1422AGMV_CNTL1_VAL;
    uint8_t cntl3_val = BM1422AGMV_CNTL3_VAL;

    result = write(BM1422AGMV_CNTL1, &cntl1_val, sizeof(cntl1_val));
    if (result == BM1422AGMV_OK) {
        (void)write(BM1422AGMV_CNTL3, &cntl3_val, sizeof(cntl3_val));
    } else {
        result = BM1422AGMV_COMM_ERROR;
    }

    return result;
}

int32_t BM1422AGMV::stop(void)
{
    int32_t result;
    uint8_t val = BM1422AGMV_CNTL1_VAL | BM1422AGMV_CNTL1_FS1_SINGLE;

    result = write(BM1422AGMV_CNTL1, &val, sizeof(val));

    return result;
}

int32_t BM1422AGMV::get_val(uint8_t *raw)
{
    int32_t result;

    result = read(BM1422AGMV_DATAX, raw, BM1422AGMV_RAW_DATA_SIZE);

    return result;
}

int32_t BM1422AGMV::get_val(float32 *mag)
{
    int32_t result;
    uint8_t cnt;
    uint8_t raw[BM1422AGMV_RAW_DATA_SIZE];
    int16_t data[BM1422AGMV_DATA_SIZE];
    uint8_t sensitivity;

    result = get_val(raw);
    if (result == BM1422AGMV_OK) {
        data[0] = ((int16_t)raw[1] << 8) | raw[0];
        data[1] = ((int16_t)raw[3] << 8) | raw[2];
        data[2] = ((int16_t)raw[5] << 8) | raw[4];

        sensitivity = calc_sensitivity();

        for (cnt = 0; cnt < BM1422AGMV_DATA_SIZE; cnt++) {
            mag[cnt] = (float32)data[cnt] * 0.042;
        }
    } else {
        result = BM1422AGMV_COMM_ERROR;
    }

    return result;
}

float32 BM1422AGMV::get_version(void)
{
    return BM1422AGMV_DRIVER_VERSION;
}

int32_t BM1422AGMV::init_check_val(void)
{
    int32_t result;
    uint8_t read_val = 0;

    result = read(BM1422AGMV_WIA, &read_val, sizeof(read_val));
    if (result == BM1422AGMV_OK) {
        if (read_val == BM1422AGMV_WAI_VAL) {
            result = BM1422AGMV_OK;
        } else {
            result = BM1422AGMV_WAI_ERROR;
        }
    } else {
        result = BM1422AGMV_COMM_ERROR;
    }

    return result;
}

int32_t BM1422AGMV::init_setting_ic(void)
{
    int32_t result;
    uint8_t cntl1_val = BM1422AGMV_CNTL1_VAL;
    uint8_t cntl2_val = BM1422AGMV_CNTL2_VAL;
    uint8_t ave_a_val = BM1422AGMV_AVE_A_VAL;
    uint16_t cntl4_val = BM1422AGMV_CNTL4_VAL;

    result = write(BM1422AGMV_CNTL1, &cntl1_val, sizeof(cntl1_val));
    if (result == BM1422AGMV_OK) {
        (void)write(BM1422AGMV_CNTL4, (uint8_t*)&cntl4_val, sizeof(cntl4_val));
        (void)write(BM1422AGMV_CNTL2, &cntl2_val, sizeof(cntl2_val));
        (void)write(BM1422AGMV_AVE_A, &ave_a_val, sizeof(ave_a_val));
    } else {
        result = BM1422AGMV_COMM_ERROR;
    }

    return result;
}

uint8_t BM1422AGMV::calc_sensitivity(void)
{
    uint8_t val = BM1422AGMV_CNTL1_VAL;
    uint8_t sensitivity;

    val &= BM1422AGMV_CNTL1_OUT_BIT_MASK;

    //Out_bit  14bit:24, 12bit:6
    sensitivity = (9 * (val >> 5)) + 6;

    return sensitivity;
}


int32_t BM1422AGMV::write(uint8_t reg, uint8_t *data, int32_t size)
{
    int32_t result;

    Wire.beginTransmission(Address);
    (void)Wire.write(reg);
    (void)Wire.write(data, (uint8_t)size);
    result = Wire.endTransmission();
    if (result == 0) {
        result = BM1422AGMV_OK;
    } else {
        result = BM1422AGMV_COMM_ERROR;
    }

    return result;
}

int32_t BM1422AGMV::read(uint8_t reg, uint8_t *data, int32_t size)
{
    int32_t result;
    uint8_t cnt;
    uint8_t receive_size;

    Wire.beginTransmission(Address);
    (void)Wire.write(reg);
    result = Wire.endTransmission(false);
    if (result == 0) {
        receive_size = Wire.requestFrom(Address, (uint8_t)size);
        if (receive_size == size) {
            for (cnt = 0; cnt < size; cnt++) {
                data[cnt] = Wire.read();
            }
            result = BM1422AGMV_OK;
        } else {
            result = BM1422AGMV_COMM_ERROR;
        }
    } else {
        result = BM1422AGMV_COMM_ERROR;
    }

    return result;
}


int32_t BM1422AGMV::wia_read(uint8_t reg, uint8_t data, int32_t size) {

    read(reg, &data, size);
    return data;

}








