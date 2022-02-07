/*
 * BMI160.h
 *
 *  Created on: Nov 18, 2021
 *      Author: Justin Kim
 */

#ifndef INC_BMI160_H_
#define INC_BMI160_H_

#include <os_hal_i2c.h>

#define BMI160_ADDR_DEFAULT 0x68
#define BMI160_ADDR_PULLUP 0x69
#define ACC_SET_PMU_MODE 16
#define GYR_SET_PMU_MODE 20
#define MAG_SET_PMU_MODE 24


enum PowerModes
{
    SUSPEND = 0,  ///<Acc and Gyro, No sampling, No FIFO data readout
    NORMAL,       ///<Acc and Gyro, Full chip operation
    LOW_POWER,    ///<Acc duty-cycling between suspend and normal
    FAST_START_UP ///<Gyro start up delay time to normal mode <= 10 ms
};

enum AccRange
{
    SENS_2G = 0x03,  ///<Accelerometer range +-2G
    SENS_4G = 0x05,  ///<Accelerometer range +-4G
    SENS_8G = 0x08,  ///<Accelerometer range +-8G
    SENS_16G = 0x0C ///<Accelerometer range +-16G
};

///Accelerometer undersampling
enum AccUnderSampling
{
    ACC_US_OFF = 0,
    ACC_US_ON
};

///Accelerometer bandwidth parameters
enum AccBandWidthParam
{
    ACC_BWP_0 = 0, ///< Average 1 cycle;  when acc_us = 0 OSR4
    ACC_BWP_1,     ///< Average 2 cycles; when acc_us = 0 OSR2
    ACC_BWP_2,     ///< Average 4 cycles; when acc_us = 0 normal mode
    ACC_BWP_3,     ///< Average 8 cycles
    ACC_BWP_4,     ///< Average 16 cycles
    ACC_BWP_5,     ///< Average 32 cycles
    ACC_BWP_6,     ///< Average 64 cycles
    ACC_BWP_7      ///< Average 128 cycles
};

///Accelerometer output data rates
enum AccOutputDataRate
{
    ACC_ODR_1 = 1,  ///< 25/32Hz
    ACC_ODR_2,      ///< 25/16Hz
    ACC_ODR_3,      ///< 25/8Hz
    ACC_ODR_4,      ///< 25/4Hz
    ACC_ODR_5,      ///< 25/2Hz
    ACC_ODR_6,      ///< 25Hz
    ACC_ODR_7,      ///< 50Hz
    ACC_ODR_8,      ///< 100Hz
    ACC_ODR_9,      ///< 200Hz
    ACC_ODR_10,     ///< 400Hz
    ACC_ODR_11,     ///< 800Hz
    ACC_ODR_12      ///< 1600Hz
};

enum Registers
{
    CHIP_ID = 0x00,  ///<Chip Identification.
    ERR_REG = 0x02,  ///<Reports sensor error flags.  Flags reset when read.
    PMU_STATUS,      ///<Reports current power mode for sensors.
    DATA_0,          ///<MAG_X axis bits7:0
    DATA_1,          ///<MAG_X axis bits15:8
    DATA_2,          ///<MAG_Y axis bits7:0
    DATA_3,          ///<MAG_Y axis bits15:8
    DATA_4,          ///<MAG_Z axis bits7:0
    DATA_5,          ///<MAG_Z axis bits15:8
    DATA_6,          ///<RHALL bits7:0
    DATA_7,          ///<RHALL bits15:8
    DATA_8,          ///<GYR_X axis bits7:0
    DATA_9,          ///<GYR_X axis bits15:8
    DATA_10,         ///<GYR_Y axis bits7:0
    DATA_11,         ///<GYR_Y axis bits15:8
    DATA_12,         ///<GYR_Z axis bits7:0
    DATA_13,         ///<GYR_Z axis bits15:8
    DATA_14,         ///<ACC_X axis bits7:0
    DATA_15,         ///<ACC_X axis bits15:8
    DATA_16,         ///<ACC_Y axis bits7:0
    DATA_17,         ///<ACC_Y axis bits15:8
    DATA_18,         ///<ACC_Z axis bits7:0
    DATA_19,         ///<ACC_Z axis bits15:8
    SENSORTIME_0,    ///<24bit counter synchronized with data, bits7:0
    SENSORTIME_1,    ///<24bit counter synchronized with data, bits15:8
    SENSORTIME_2,    ///<24bit counter synchronized with data, bits23:16
    STATUS,          ///<Reports sensors status flags
    INT_STATUS_0,    ///<Contains interrupt status flags
    INT_STATUS_1,    ///<Contains interrupt status flags
    INT_STATUS_2,    ///<Contains interrupt status flags
    INT_STATUS_3,    ///<Contains interrupt status flags
    TEMPERATURE_0,   ///<Contains temperature of sensor, bits7:0
    TEMPERATURE_1,   ///<Contains temperature of sensor, bits15:8
    FIFO_LENGTH_0,   ///<Current fill level of FIFO, bits7:0
    FIFO_LENGTH_1,   ///<Current fill level of FIFO, bits10:8
    FIFO_DATA,       ///<FIFO data read out register, burst read
    ACC_CONF = 0x40, ///<Set ODR, bandwidth, and read mode of accelerometer
    ACC_RANGE,       ///<Sets accelerometer g-range
    GYR_CONF,        ///<Set ODR, bandwidth, and read mode of gyroscope
    GYR_RANGE,       ///<Sets gyroscope angular rate measurement range
    MAG_CONF,        ///<Sets ODR of magnetometer interface
    FIFO_DOWNS,      ///<Sets down sampling ratios of accel and gyro data
                     ///<for FIFO
                     FIFO_CONFIG_0,   ///<Sets FIFO Watermark
                     FIFO_CONFIG_1,   ///<Sets which sensor data is available in FIFO,
                                      ///<Header/Headerless mode, Ext Int tagging, Sensortime
                                      MAG_IF_0 = 0x4B, ///<Magnetometer 7-bit I2C address, bits7:1
                                      MAG_IF_1,        ///<Magnetometer interface configuration
                                      MAG_IF_2,        ///<Magnetometer address to read
                                      MAG_IF_3,        ///<Magnetometer address to write
                                      MAG_IF_4,        ///<Magnetometer data to write
                                      INT_EN_0,        ///<Interrupt enable bits
                                      INT_EN_1,        ///<Interrupt enable bits
                                      INT_EN_2,        ///<Interrupt enable bits
                                      INT_OUT_CTRL,    ///<Contains the behavioral configuration of INT pins
                                      INT_LATCH,       ///<Contains the interrupt rest bit and the interrupt
                                                       ///<mode selection
                                                       INT_MAP_0,       ///<Controls which interrupt signals are mapped to the
                                                                        ///<INT1 and INT2 pins
                                                                        INT_MAP_1,       ///<Controls which interrupt signals are mapped to the
                                                                                         ///<INT1 and INT2 pins
                                                                                         INT_MAP_2,       ///<Controls which interrupt signals are mapped to the
                                                                                                          ///<INT1 and INT2 pins
                                                                                                          INT_DATA_0,      ///<Contains the data source definition for the two
                                                                                                                           ///<interrupt groups
                                                                                                                           INT_DATA_1,      ///<Contains the data source definition for the two
                                                                                                                                            ///<interrupt groups
                                                                                                                                            INT_LOWHIGH_0,   ///<Contains the configuration for the low g interrupt
                                                                                                                                            INT_LOWHIGH_1,   ///<Contains the configuration for the low g interrupt
                                                                                                                                            INT_LOWHIGH_2,   ///<Contains the configuration for the low g interrupt
                                                                                                                                            INT_LOWHIGH_3,   ///<Contains the configuration for the low g interrupt
                                                                                                                                            INT_LOWHIGH_4,   ///<Contains the configuration for the low g interrupt
                                                                                                                                            INT_MOTION_0,    ///<Contains the configuration for the any motion and
                                                                                                                                                             ///<no motion interrupts
                                                                                                                                                             INT_MOTION_1,    ///<Contains the configuration for the any motion and
                                                                                                                                                                              ///<no motion interrupts
                                                                                                                                                                              INT_MOTION_2,    ///<Contains the configuration for the any motion and
                                                                                                                                                                                               ///<no motion interrupts
                                                                                                                                                                                               INT_MOTION_3,    ///<Contains the configuration for the any motion and
                                                                                                                                                                                                                ///<no motion interrupts
                                                                                                                                                                                                                INT_TAP_0,       ///<Contains the configuration for the tap interrupts
                                                                                                                                                                                                                INT_TAP_1,       ///<Contains the configuration for the tap interrupts
                                                                                                                                                                                                                INT_ORIENT_0,    ///<Contains the configuration for the oeientation
                                                                                                                                                                                                                                 ///<interrupt
                                                                                                                                                                                                                                 INT_ORIENT_1,    ///<Contains the configuration for the oeientation
                                                                                                                                                                                                                                                  ///<interrupt
                                                                                                                                                                                                                                                  INT_FLAT_0,      ///<Contains the configuration for the flat interrupt
                                                                                                                                                                                                                                                  INT_FLAT_1,      ///<Contains the configuration for the flat interrupt
                                                                                                                                                                                                                                                  FOC_CONF,        ///<Contains configuration for the fast offset
                                                                                                                                                                                                                                                                   ///<compensation for the accelerometer and gyroscope
                                                                                                                                                                                                                                                                   CONF,            ///<Configuration of sensor, nvm_prog_en bit
                                                                                                                                                                                                                                                                   IF_CONF,         ///<Contains settings for the digital interface
                                                                                                                                                                                                                                                                   PMU_TRIGGER,     ///<Sets trigger conditions to change gyro power modes
                                                                                                                                                                                                                                                                   SELF_TEST,       ///<Self test configuration
                                                                                                                                                                                                                                                                   NV_CONF = 0x70,  ///<Contains settings for the digital interface
                                                                                                                                                                                                                                                                   OFFSET_0,        ///<Contains offset comp values for acc_off_x7:0
                                                                                                                                                                                                                                                                   OFFSET_1,        ///<Contains offset comp values for acc_off_y7:0
                                                                                                                                                                                                                                                                   OFFSET_2,        ///<Contains offset comp values for acc_off_z7:0
                                                                                                                                                                                                                                                                   OFFSET_3,        ///<Contains offset comp values for gyr_off_x7:0
                                                                                                                                                                                                                                                                   OFFSET_4,        ///<Contains offset comp values for gyr_off_y7:0
                                                                                                                                                                                                                                                                   OFFSET_5,        ///<Contains offset comp values for gyr_off_z7:0
                                                                                                                                                                                                                                                                   OFFSET_6,        ///<gyr/acc offset enable bit and gyr_off_(zyx) bits9:8
                                                                                                                                                                                                                                                                   STEP_CNT_0,      ///<Step counter bits 15:8
                                                                                                                                                                                                                                                                   STEP_CNT_1,      ///<Step counter bits 7:0
                                                                                                                                                                                                                                                                   STEP_CONF_0,     ///<Contains configuration of the step detector
                                                                                                                                                                                                                                                                   STEP_CONF_1,     ///<Contains configuration of the step detector
                                                                                                                                                                                                                                                                   CMD = 0x7E       ///<Command register triggers operations like
                                                                                                                                                                                                                                                                                    ///<softreset, NVM programming, etc.
};

static const uint8_t ACC_ODR_MASK = 0x0F;
static const uint8_t ACC_ODR_POS = 0x00;
static const uint8_t ACC_BWP_MASK = 0x70;
static const uint8_t ACC_BWP_POS = 0x04;
static const uint8_t ACC_US_MASK = 0x80;
static const uint8_t ACC_US_POS = 0x07;
static const uint8_t ACC_RANGE_MASK = 0x0F;
static const uint8_t ACC_RANGE_POS = 0x00;

static const float SENS_2G_LSB_PER_G = 16384.0F;
static const float SENS_4G_LSB_PER_G = 8192.0F;
static const float SENS_8G_LSB_PER_G = 4096.0F;
static const float SENS_16G_LSB_PER_G = 2048.0F;

void Error();

bool InitBMI160();

bool ReadBMI160(uint8_t* data);

bool GetSensorData(float* xData, float* yData, float* zData);

bool FillSensorData(float* dataBuffer, int size);

#endif /* INC_BMI160_H_ */
