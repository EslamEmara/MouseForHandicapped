/*
 * BNO005_CONFIG.h
 *
 * Created: 10/3/2021 7:31:34 PM
 *  Author: Omar
 */ 


#ifndef BNO005_CONFIG_H_
#define BNO005_CONFIG_H_

#define ADO					 0					/*i2c adress*/
#define OPERATION_FREQ		FREQ_16Mhz

#define OP_MODE NDOF
#define ACC_CONFIGS NormalA << 5 | ABW_31_25Hz << 2 | AFS_2G
#define GYRO_BW_RANGE GBW_23Hz << 3 | GFS_250DPS // bandwidth and rate in dps
#define GYRO_POWER_MODE NormalG // power mode
#define MAG_CONFIGS Normal << 5 | Regular << 3 | MODR_10Hz  
#define PWR_MODE Normalpwr
#define SYS_UNITS 0x01 //temperature in degrees C, rate in dps, accel in mg



#endif /* BNO005_CONFIG_H_ */