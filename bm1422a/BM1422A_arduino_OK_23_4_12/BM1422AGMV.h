/*****************************************************************************
  BM1422AGMV.h

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
#ifndef BM1422AGMV_H_
#define BM1422AGMV_H_

#ifndef float32
#define float32                       float
#endif

// Error Number
#define BM1422AGMV_OK                 (0)
#define BM1422AGMV_COMM_ERROR         (-1)
#define BM1422AGMV_WAI_ERROR          (-2)
// Slave Address
#define BM1422AGMV_SLAVE_ADDRESS_0E   (0x0E)
#define BM1422AGMV_SLAVE_ADDRESS_0F   (0x0F)
#define BM1422AGMV_ADDR_HIGH          (true)
#define BM1422AGMV_ADDR_LOW           (false)
// Register Address
#define BM1422AGMV_WIA                (0x0F)
#define BM1422AGMV_DATAX              (0x10)
#define BM1422AGMV_STA1               (0x18)
#define BM1422AGMV_CNTL1              (0x1B)
#define BM1422AGMV_CNTL2              (0x1C)
#define BM1422AGMV_CNTL3              (0x1D)
#define BM1422AGMV_AVE_A              (0x40)
#define BM1422AGMV_CNTL4              (0x5C)
// Register Parameter
#define BM1422AGMV_STA1_RD_DRDY_OK    (1 << 6)
#define BM1422AGMV_CNTL1_FS1_SINGLE   (1 << 1)
#define BM1422AGMV_CNTL1_RST_LV_LOW   (0 << 5)
#define BM1422AGMV_CNTL1_OUT_BIT      (1 << 6)
#define BM1422AGMV_CNTL1_PC1_ACTIVE   (1 << 7)
#define BM1422AGMV_CNTL2_DREN_DISABLE (0 << 3)
#define BM1422AGMV_CNTL3_FORCE        (1 << 6)
#define BM1422AGMV_AVE_A_4            (0 << 2)
// Register Value(write)
#define BM1422AGMV_CNTL1_VAL          (BM1422AGMV_CNTL1_PC1_ACTIVE | BM1422AGMV_CNTL1_OUT_BIT | BM1422AGMV_CNTL1_RST_LV_LOW | BM1422AGMV_CNTL1_FS1_SINGLE)
#define BM1422AGMV_CNTL2_VAL          (BM1422AGMV_CNTL2_DREN_DISABLE)
#define BM1422AGMV_CNTL3_VAL          (BM1422AGMV_CNTL3_FORCE)
#define BM1422AGMV_CNTL4_VAL          (0x0000)
#define BM1422AGMV_AVE_A_VAL          (BM1422AGMV_AVE_A_4)
// Register Value(read)
#define BM1422AGMV_WAI_VAL            (0x41)
// Meas Time
#define BM1422AGMV_MEAS_TIME          (3)
// Mask
#define BM1422AGMV_CNTL1_OUT_BIT_MASK (0x40)
// Version
#define BM1422AGMV_DRIVER_VERSION     (1.1F)
// Sensitivity
#define BM1422AGMV_14BIT_SENSITIVITY  (24)
#define BM1422AGMV_12BIT_SENSITIVITY  (6)
// Others
#define BM1422AGMV_RAW_DATA_SIZE      (6)
#define BM1422AGMV_DATA_SIZE          (3)

class BM1422AGMV
{
    public:
        BM1422AGMV(bool addr_pin);
        ~BM1422AGMV();
        int32_t init(void);
        int32_t start(void);
        int32_t stop(void);
        int32_t get_val(uint8_t *raw);
        int32_t get_val(float32 *mag);
        int32_t wia_read(uint8_t reg, uint8_t data, int32_t size);
        float32 get_version(void);

    private:
        uint8_t Address;

        int32_t init_check_val(void);
        int32_t init_setting_ic(void);
        uint8_t calc_sensitivity(void);
        int32_t write(uint8_t reg, uint8_t *data, int32_t size);
        int32_t read(uint8_t reg, uint8_t *data, int32_t size);
};

#endif // BM1422AGMV_H_
