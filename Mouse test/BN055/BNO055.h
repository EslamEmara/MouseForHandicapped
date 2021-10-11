/*
 * BNO055.h
 *7
 * Created: 10/2/2021 4:09:14 PM
 *  Author: Omar & Eslam
 */ 


#ifndef BNO055_H_
#define BNO055_H_

#include "BNO005_CONFIG.h"
#include "TypeDefs.h"

// BNO055 Register Map
// BNO055 Page 0
#define PAGE_0                  0x00
#define PAGE_1                  0x01
#define BNO055_CHIP_ID          0x00    // should be 0xA0
#define BNO055_ACC_ID           0x01    // should be 0xFB
#define BNO055_MAG_ID           0x02    // should be 0x32
#define BNO055_GYRO_ID          0x03    // should be 0x0F
#define BNO055_SW_REV_ID_LSB    0x04
#define BNO055_SW_REV_ID_MSB    0x05
#define BNO055_BL_REV_ID        0x06
#define BNO055_PAGE_ID          0x07
#define BNO055_ACC_DATA_X_LSB   0x08
#define BNO055_ACC_DATA_X_MSB   0x09
#define BNO055_ACC_DATA_Y_LSB   0x0A
#define BNO055_ACC_DATA_Y_MSB   0x0B
#define BNO055_ACC_DATA_Z_LSB   0x0C
#define BNO055_ACC_DATA_Z_MSB   0x0D
#define BNO055_MAG_DATA_X_LSB   0x0E
#define BNO055_MAG_DATA_X_MSB   0x0F
#define BNO055_MAG_DATA_Y_LSB   0x10
#define BNO055_MAG_DATA_Y_MSB   0x11
#define BNO055_MAG_DATA_Z_LSB   0x12
#define BNO055_MAG_DATA_Z_MSB   0x13
#define BNO055_GYR_DATA_X_LSB   0x14
#define BNO055_GYR_DATA_X_MSB   0x15
#define BNO055_GYR_DATA_Y_LSB   0x16
#define BNO055_GYR_DATA_Y_MSB   0x17
#define BNO055_GYR_DATA_Z_LSB   0x18
#define BNO055_GYR_DATA_Z_MSB   0x19
#define BNO055_EUL_HEADING_LSB  0x1A
#define BNO055_EUL_HEADING_MSB  0x1B
#define BNO055_EUL_ROLL_LSB     0x1C
#define BNO055_EUL_ROLL_MSB     0x1D
#define BNO055_EUL_PITCH_LSB    0x1E
#define BNO055_EUL_PITCH_MSB    0x1F
#define BNO055_QUA_DATA_W_LSB   0x20
#define BNO055_QUA_DATA_W_MSB   0x21
#define BNO055_QUA_DATA_X_LSB   0x22
#define BNO055_QUA_DATA_X_MSB   0x23
#define BNO055_QUA_DATA_Y_LSB   0x24
#define BNO055_QUA_DATA_Y_MSB   0x25
#define BNO055_QUA_DATA_Z_LSB   0x26
#define BNO055_QUA_DATA_Z_MSB   0x27
#define BNO055_LIA_DATA_X_LSB   0x28
#define BNO055_LIA_DATA_X_MSB   0x29
#define BNO055_LIA_DATA_Y_LSB   0x2A
#define BNO055_LIA_DATA_Y_MSB   0x2B
#define BNO055_LIA_DATA_Z_LSB   0x2C
#define BNO055_LIA_DATA_Z_MSB   0x2D
#define BNO055_GRV_DATA_X_LSB   0x2E
#define BNO055_GRV_DATA_X_MSB   0x2F
#define BNO055_GRV_DATA_Y_LSB   0x30
#define BNO055_GRV_DATA_Y_MSB   0x31
#define BNO055_GRV_DATA_Z_LSB   0x32
#define BNO055_GRV_DATA_Z_MSB   0x33
#define BNO055_TEMP             0x34
#define BNO055_CALIB_STAT       0x35
#define BNO055_ST_RESULT        0x36
#define BNO055_INT_STATUS       0x37
#define BNO055_SYS_CLK_STATUS   0x38
#define BNO055_SYS_STATUS       0x39
#define BNO055_SYS_ERR          0x3A
#define BNO055_UNIT_SEL         0x3B
#define BNO055_OPR_MODE         0x3D
#define BNO055_PWR_MODE         0x3E
#define BNO055_SYS_TRIGGER      0x3F
#define BNO055_TEMP_SOURCE      0x40
#define BNO055_AXIS_MAP_CONFIG  0x41
#define BNO055_AXIS_MAP_SIGN    0x42
#define BNO055_ACC_OFFSET_X_LSB 0x55
#define BNO055_ACC_OFFSET_X_MSB 0x56
#define BNO055_ACC_OFFSET_Y_LSB 0x57
#define BNO055_ACC_OFFSET_Y_MSB 0x58
#define BNO055_ACC_OFFSET_Z_LSB 0x59
#define BNO055_ACC_OFFSET_Z_MSB 0x5A
#define BNO055_MAG_OFFSET_X_LSB 0x5B
#define BNO055_MAG_OFFSET_X_MSB 0x5C
#define BNO055_MAG_OFFSET_Y_LSB 0x5D
#define BNO055_MAG_OFFSET_Y_MSB 0x5E
#define BNO055_MAG_OFFSET_Z_LSB 0x5F
#define BNO055_MAG_OFFSET_Z_MSB 0x60
#define BNO055_GYR_OFFSET_X_LSB 0x61
#define BNO055_GYR_OFFSET_X_MSB 0x62
#define BNO055_GYR_OFFSET_Y_LSB 0x63
#define BNO055_GYR_OFFSET_Y_MSB 0x64
#define BNO055_GYR_OFFSET_Z_LSB 0x65
#define BNO055_GYR_OFFSET_Z_MSB 0x66
#define BNO055_ACC_RADIUS_LSB   0x67
#define BNO055_ACC_RADIUS_MSB   0x68
#define BNO055_MAG_RADIUS_LSB   0x69
#define BNO055_MAG_RADIUS_MSB   0x6A
//
// BNO055 Page 1
#define BNO055_PAGE_ID          0x07
#define BNO055_ACC_CONFIG       0x08
#define BNO055_MAG_CONFIG       0x09
#define BNO055_GYRO_CONFIG_0    0x0A
#define BNO055_GYRO_CONFIG_1    0x0B
#define BNO055_ACC_SLEEP_CONFIG 0x0C
#define BNO055_GYR_SLEEP_CONFIG 0x0D
#define BNO055_INT_MSK          0x0F
#define BNO055_INT_EN           0x10
#define BNO055_ACC_AM_THRES     0x11
#define BNO055_ACC_INT_SETTINGS 0x12
#define BNO055_ACC_HG_DURATION  0x13
#define BNO055_ACC_HG_THRESH    0x14
#define BNO055_ACC_NM_THRESH    0x15
#define BNO055_ACC_NM_SET       0x16
#define BNO055_GYR_INT_SETTINGS 0x17
#define BNO055_GYR_HR_X_SET     0x18
#define BNO055_GYR_DUR_X        0x19
#define BNO055_GYR_HR_Y_SET     0x1A
#define BNO055_GYR_DUR_Y        0x1B
#define BNO055_GYR_HR_Z_SET     0x1C
#define BNO055_GYR_DUR_Z        0x1D
#define BNO055_GYR_AM_THRESH    0x1E
#define BNO055_GYR_AM_SET       0x1F


// Using the BNO055_BMP280 breakout board/Teensy 3.1 Add-On Shield, ADO is set to 1 by default
#if ADO
#define BNO055_ADDRESS 0x29   //  Device address of BNO055 when ADO = 1
#else
#define BNO055_ADDRESS 0x28   //  Device address of BNO055 when ADO = 0
#endif

// Set initial input parameters
enum Ascale {  // ACC Full Scale
  AFS_2G = 0,
  AFS_4G,
  AFS_8G,
  AFS_18G
};

enum Abw { // ACC Bandwidth
  ABW_7_81Hz = 0,
  ABW_15_63Hz,
  ABW_31_25Hz,
  ABW_62_5Hz,
  ABW_125Hz,
  ABW_250Hz,
  ABW_500Hz,
  ABW_1000Hz,    //0x07
};

enum APwrMode { // ACC Pwr Mode
  NormalA = 0,
  SuspendA,
  LowPower1A,
  StandbyA,
  LowPower2A,
  DeepSuspendA
};

enum Gscale {  // gyro full scale
  GFS_2000DPS = 0,
  GFS_1000DPS,
  GFS_500DPS,
  GFS_250DPS,
  GFS_125DPS    // 0x04
};

enum GPwrMode { // GYR Pwr Mode
  NormalG = 0,
  FastPowerUpG,
  DeepSuspendedG,
  SuspendG,
  AdvancedPowerSaveG
};

enum Gbw { // gyro bandwidth
  GBW_523Hz = 0,
  GBW_230Hz,
  GBW_116Hz,
  GBW_47Hz,
  GBW_23Hz,
  GBW_12Hz,
  GBW_64Hz,
  GBW_32Hz
};

enum OPRMode {  // BNO-55 operation modes
  CONFIGMODE = 0x00,
  // Sensor Mode
  ACCONLY,
  MAGONLY,
  GYROONLY,
  ACCMAG,
  ACCGYRO,
  MAGGYRO,
  AMG,            // 0x07
  // Fusion Mode
  IMU,
  COMPASS,
  M4G,
  NDOF_FMC_OFF,
  NDOF            // 0x0C
};

enum PWRMode {
  Normalpwr = 0,
  Lowpower,
  Suspendpwr
};

enum Modr {         // magnetometer output data rate
  MODR_2Hz = 0,
  MODR_6Hz,
  MODR_8Hz,
  MODR_10Hz,
  MODR_15Hz,
  MODR_20Hz,
  MODR_25Hz,
  MODR_30Hz
};

enum MOpMode { // MAG Op Mode
  LowPower = 0,
  Regular,
  EnhancedRegular,
  HighAccuracy
};

enum MPwrMode { // MAG power mode
  Normal = 0,
  Sleep,
  Suspend,
  ForceMode
};

typedef enum{         /*sensor types*/
  SYSTEM,
  GYROSCOPE,
  ACCELOMETER,
  MAGNETOMETER,
}EN_SENSOR_t;

typedef enum{         /*sensor fails*/
  ACCELOMETER_FAIL=5,
  MAGNETOMETER_FAIL,
  GYROSCOPE_FAIL,
  SYSTEM_FAIL,
  BNO055_SUCCESS,
}EN_FAIL_t;

typedef enum{       /*calibration status*/
  NOT_CALIBRATED,
  LOW_CALIBRATED,
  PARTIALLY_CALIBRATED,
  FULL_CALIBRATED,
}EN_CALIBRATION_t;

typedef struct offsets{   /*sensors offsets and radius*/
  s32_t ACCEL_OFFSET[3];
  s32_t GYRO_OFFSET[3];
  s32_t MAG_OFFSET[3];
  s32_t ACCEL_RADIUS;
  s32_t MAG_RADIUS;
}ST_BIAS_t;

/****************************************************** FUNCTIONS PROTOTYPES *************************************************/

/*
*Function to initalize BNO055 with related configrations in config file
*return: EN_FAIL_t in case of any sensor fail in self test
*the function stucks in a loop till the calibration is completed for reliable values
*to speed up calibration process you can use GetOffsets and Get Radius functions and SetCalibProfile
*Functions to store calibrated offsets after every boot
*
*/
EN_FAIL_t BNO055_Init();

void BNO055_WriteByte(u8_t address, u8_t subAddress, u8_t data);
u8_t BNO055_ReadByte(u8_t address, u8_t subAddress);
void BNO055_ReadBytes(u8_t address, u8_t subAddress, u8_t count, u8_t * data);

EN_CALIBRATION_t BNO055_GetCalibStat(EN_SENSOR_t sensor);
/*
* Function to read the accelometer data
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the 
          acceleration in x ,y ,z
* void return
*
*/
void BNO055_ReadAcc(s16_t * destination);

/*
* Function to read the gyroscope data
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the 
          gyroscope in x ,y ,z
* void return
*
*/
void BNO055_ReadGyro(s16_t * destination);

/*
* Function to read the magnetometer data
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the 
          magnetometer in x ,y ,z
* void return
*
*/
void BNO055_ReadMag(s16_t * destination);

/*
* Function to read the euler andles data from the sensor
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the 
          angles in x ,y ,z   (yaw,roll,pitch)
* void return
*
*/
void BNO055_ReadEulerAngles(s16_t * destination);


/*
* Function to Get Gyro offsets to be used for fast calibration (must be called after FULL_CALIBRATED)
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the
            Gyro offsets in x ,y ,z
*/
void BNO055_GetGyroOffsets(s32_t* gyro_bias);

/*
* Function to set Gyro offsets by pre known values for fast calibration
* input parameter: s16_t pointer to first element of array of 3 elements that will hold the
            Gyro offsets in x ,y ,z
*/
void BNO055_SetGyroOffsets(s32_t* gyro_bias);

/*
* Function to Get accelometer offsets to be used for fast calibration (must be called after FULL_CALIBRATED)
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the
            accelometer offsets in x ,y ,z
*/
void BNO055_GetAccOffsets(s32_t* accel_bias);

/*
* Function to set accelometer offsets by pre known values for fast calibration
* input parameter: s16_t pointer to first element of array of 3 elements that will hold the
            accelometer offsets in x ,y ,z
*/
void BNO055_SetAccOffsets(s32_t* accel_bias);

/*
* Function to Get Magnetometer offsets to be used for fast calibration (must be called after FULL_CALIBRATED)
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the
            Magnetometer offsets in x ,y ,z
*/
void BNO055_GetMagOffsets(s32_t* mag_bias);

/*
* Function to set Magnetometer offsets by pre known values for fast calibration
* input parameter: s16_t pointer to first element of array of 3 elements that will hold the
            Magnetometer offsets in x ,y ,z
*/
void BNO055_SetMagOffsets(s32_t* mag_bias);

/*Function to set the calibration offsets and radius of all sensors together with saved value
*save value must be saved after a FULL_CALIBRATED mode and be loaded into regs after every bootup for fast calibration
*inputs ST_BIAS_t that holds offsets and radius     (see BNO055.h for definition)*
*
*/
void BNO055_SetCalibratioProfile(ST_BIAS_t bias);

/*
* Function to Get Magnetometer radius to be used for fast calibration (must be called after FULL_CALIBRATED)
* output parameter: s16_t variable that holds the radius value of Magnetometer
*/
s16_t BNO055_GetMagRadius();

/*
* Function to set Magnetometer radius by pre known values for fast calibration
* input parameter: s32_t variable that holds the radius value
*/
void BNO055_SetMagRadius(s32_t mag_radius);

/*
* Function to Get Accelometer radius to be used for fast calibration (must be called after FULL_CALIBRATED)
* output parameter: s16_t variable that holds the radius value of accelometer
*/
s16_t BNO055_GetAccRadius();

/*
* Function to set Accelometer radius by pre known values for fast calibration
* input parameter: s32_t variable that holds the radius value
*/
void BNO055_SetAccRadius(s32_t accel_radius);


/*
*Function to Test the sensors see if they fail in hardware or not
*return EN_FAIL_t of the failed sensor (see BNO055.h for definition)
*   return
*/
EN_FAIL_t BNO055_SelfTest();

#endif /* BNO055_H_ */
