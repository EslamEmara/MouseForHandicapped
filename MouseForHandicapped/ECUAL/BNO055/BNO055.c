/*
 * BNO055.c
 *
 * Created: 10/2/2021 4:08:32 PM
 *  Author: Omar & Eslam
 */ 
#include "BNO055.h"

/*
*Function to initalize BNO055 with related configrations in config file
*return: EN_FAIL_t in case of any sensor fail in self test
*the function stucks in a loop till the calibration is completed for reliable values
*to speed up calibration process you can use GetOffsets and Get Radius functions and SetCalibProfile
*Functions to store calibrated offsets after every boot 
*
*/
EN_FAIL_t BNO055_Init()
{	
	I2C_Init(OPERATION_FREQ,100000);					/*initialize i2c with frequency 100Khz*/
	
	/*=============================== init test 1 ===========================*/
	/*BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
	// Select page 1 to configure sensors
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_PAGE_ID, PAGE_1);
	// Configure ACC
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_CONFIG, ACC_CONFIGS );
	// Configure GYR
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYRO_CONFIG_0, GYRO_BW_RANGE );
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYRO_CONFIG_1, GYRO_POWER_MODE);
	// Configure MAG
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_CONFIG, MAG_CONFIGS );
	// Select page 0 to read sensors
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_PAGE_ID, PAGE_0);
	// Select BNO055 gyro temperature source
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_TEMP_SOURCE, 0x01 );
	// Select BNO055 sensor units (temperature in degrees C, rate in dps, accel in mg)
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_UNIT_SEL, SYS_UNITS );
	// Select BNO055 system power mode
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_PWR_MODE, PWR_MODE );
	// Select BNO055 system operation mode
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, OP_MODE  );*/
	
	u8_t id = BNO055_ReadByte(BNO055_ADDRESS,BNO055_CHIP_ID);
	if (id != BNO055_ID) {
		id = BNO055_ReadByte(BNO055_ADDRESS,BNO055_CHIP_ID);
		if (id != BNO055_ID) {
			return SYSTEM_FAIL;
		}
	}
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
	BNO055_WriteByte(BNO055_ADDRESS,BNO055_SYS_TRIGGER, 0x20);
	while (BNO055_ReadByte(BNO055_ADDRESS,BNO055_CHIP_ID) != BNO055_ID);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_PWR_MODE, PWR_MODE );
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_PAGE_ID, PAGE_0);
	BNO055_WriteByte(BNO055_ADDRESS,BNO055_SYS_TRIGGER, 0x0);

	BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, OP_MODE  );	
    BNO055_SetMagOffsets(MagOffsets);
    BNO055_SetMagRadius(MagRadius);
        
    if (BNO055_SelfTest() != BNO055_SUCCESS){             /*if self test didn't pass on all sensors*/
	    return BNO055_SelfTest();
    }
        
    while (1){
	    if(BNO055_GetCalibStat(MAGNETOMETER) == FULL_CALIBRATED )
	    break;
    }
        
    return BNO055_SUCCESS;
}


void BNO055_WriteByte(u8_t address, u8_t subAddress, u8_t data)
{
	I2C_Master_Start(address);			/*initialize i2c to slave address*/
	I2C_Master_Write(subAddress);		/*register address*/
	I2C_Master_Write(data);                 /*register new data*/
	I2C_Repeated_Start(address);          /*end frame with repeated start*/
}

u8_t BNO055_ReadByte(u8_t address, u8_t subAddress)
{
	u8_t data;
	I2C_Master_Start(address);         
	I2C_Master_Write(subAddress);	                
	I2C_Repeated_Start(address);       
	data =I2C_Read_Ack();                      
	return data;                             /* Return data read from slave register*/
}
void BNO055_ReadBytes(u8_t address, u8_t subAddress, u8_t count, u8_t * data)
{
	u8_t data_count = 0;
	I2C_Master_Start(address); 
	I2C_Master_Write(subAddress);           
	I2C_Repeated_Start(address) ;

	for (data_count= 0 ; data_count < count ;++data_count){
		data[data_count] =I2C_Read_Ack();								/*read until last element*/
	}       
	data[count] = I2C_Read_Nack();										/*read last element and sen NACK*/
}

EN_CALIBRATION_t BNO055_GetCalibStat(EN_SENSOR_t sensor){
   u8_t calstat = BNO055_ReadByte(BNO055_ADDRESS, BNO055_CALIB_STAT);
   if (sensor == SYSTEM)
    return ( (0xC0 & calstat) >> 6);                  
  else if (sensor == GYROSCOPE)
    return ( (0x30 & calstat) >> 4);
  else if (sensor == ACCELOMETER)
    return ( (0x0C & calstat) >> 2);
  else if (sensor == MAGNETOMETER)
    return ( (0x03 & calstat) >> 0);
  else 
    return 0;
   
}
/*
* Function to read the accelometer data
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the 
          acceleration in x ,y ,z
* void return
*
*/

void BNO055_ReadAcc(s16_t * destination)
{
  u8_t rawData[6];  // x/y/z accel register data stored here
  BNO055_ReadBytes(BNO055_ADDRESS, BNO055_ACC_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers into data array
  destination[0] = ((s16_t)rawData[1] << 8) | rawData[0] ;      // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((s16_t)rawData[3] << 8) | rawData[2] ;
  destination[2] = ((s16_t)rawData[5] << 8) | rawData[4] ;
}

/*
* Function to read the gyroscope data
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the 
          gyroscope in x ,y ,z
* void return
*
*/
void BNO055_ReadGyro(s16_t * destination)
{
  u8_t rawData[6];  // x/y/z gyro register data stored here
  BNO055_ReadBytes(BNO055_ADDRESS, BNO055_GYR_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((s16_t)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((s16_t)rawData[3] << 8) | rawData[2] ;
  destination[2] = ((s16_t)rawData[5] << 8) | rawData[4] ;
}
/*
* Function to read the magnetometer data
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the 
          magnetometer in x ,y ,z
* void return
*
*/
void BNO055_ReadMag(s16_t * destination)
{
  u8_t rawData[6];  // x/y/z gyro register data stored here
  BNO055_ReadBytes(BNO055_ADDRESS, BNO055_MAG_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((s16_t)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((s16_t)rawData[3] << 8) | rawData[2] ;
  destination[2] = ((s16_t)rawData[5] << 8) | rawData[4] ;
}

/*
* Function to read the euler andles data from the sensor
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the 
          angles in x ,y ,z   (yaw,roll,pitch)
* void return
*
*/
void BNO055_ReadEulerAngles(s16_t * destination)
{

  u8_t rawData[6];  // x/y/z gyro register data stored here
  BNO055_ReadBytes(BNO055_ADDRESS, BNO055_EUL_HEADING_LSB, 6, &rawData[0]);   // Read the six raw data registers sequentially into data array
  destination[0] = ((((s16_t)rawData[1] << 8) | rawData[0])  /16.0);      
  destination[1] = ((((s16_t)rawData[3] << 8) | rawData[2])  /16.0)+180.0;
  destination[2] = ((((s16_t)rawData[5] << 8) | rawData[4])  /16.0 )+180.0;
}

/*
* Function to set accelometer offsets by pre known values for fast calibration
* input parameter: s16_t pointer to first element of array of 3 elements that will hold the
            accelometer offsets in x ,y ,z
*/
void BNO055_SetAccOffsets(s32_t* accel_bias){
  
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_LSB, (s16_t)accel_bias[0] & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_MSB, ((s16_t)accel_bias[0] >> 8) & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_LSB, (s16_t)accel_bias[1] & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_MSB, ((s16_t)accel_bias[1] >> 8) & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_LSB, (s16_t)accel_bias[2] & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_MSB, ((s16_t)accel_bias[2] >> 8) & 0xFF);
}
/*
* Function to Get accelometer offsets to be used for fast calibration (must be called after FULL_CALIBRATED)
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the
            accelometer offsets in x ,y ,z
*/
void BNO055_GetAccOffsets(s32_t* accel_bias){
  s8_t low = 0;
  s8_t high = 0;
  
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
  low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_LSB);
  high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_MSB);
  accel_bias[0] = ((low & 0xFF)| (high<<8));
  
  low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_LSB);
  high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_MSB);
  accel_bias[1] = ((low & 0xFF)| (high<<8));

  low=BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_LSB);
  high =BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_MSB);
  accel_bias[2] = ((low & 0xFF)| (high<<8));
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, NDOF);

}
/*
* Function to set Gyro offsets by pre known values for fast calibration
* input parameter: s16_t pointer to first element of array of 3 elements that will hold the
            Gyro offsets in x ,y ,z
*/
void BNO055_SetGyroOffsets(s32_t* gyro_bias){
  
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_LSB, (s16_t)gyro_bias[0] & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_MSB, ((s16_t)gyro_bias[0] >> 8) & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_LSB, (s16_t)gyro_bias[1] & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_MSB, ((s16_t)gyro_bias[1] >> 8) & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_LSB, (s16_t)gyro_bias[2] & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_MSB, ((s16_t)gyro_bias[2] >> 8) & 0xFF);
}
/*
* Function to Get Gyro offsets to be used for fast calibration (must be called after FULL_CALIBRATED)
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the
            Gyro offsets in x ,y ,z
*/
void BNO055_GetGyroOffsets(s32_t* gyro_bias){
  s8_t low = 0;
  s8_t high = 0;
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
  low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_LSB);
  high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_MSB);
  gyro_bias[0] = ((low & 0xFF)| (high<<8));
  
  low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_LSB);
  high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_MSB);
  gyro_bias[1] = ((low & 0xFF)| (high<<8));

  low=BNO055_ReadByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_LSB);
  high =BNO055_ReadByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_MSB);
  gyro_bias[2] = ((low & 0xFF)| (high<<8));
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, NDOF);

}
/*
* Function to Get Magnetometer offsets to be used for fast calibration (must be called after FULL_CALIBRATED)
* i/o parameter: s16_t pointer to first element of array of 3 elements that will hold the
            Magnetometer offsets in x ,y ,z
*/
void BNO055_GetMagOffsets(s16_t* mag_bias){
  s8_t low = 0;
  s8_t high = 0;
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );

  low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_LSB);
  high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_MSB);
  mag_bias[0] = ((low & 0xFF)| (high<<8));
  
  low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_LSB);
  high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_MSB);
  mag_bias[1] = ((low & 0xFF)| (high<<8));

  low=BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_LSB);
  high =BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_MSB);
  mag_bias[2] = ((low & 0xFF)| (high<<8));
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, NDOF);
  
}
/*
* Function to set Magnetometer offsets by pre known values for fast calibration
* input parameter: s16_t pointer to first element of array of 3 elements that will hold the
            Magnetometer offsets in x ,y ,z
*/
void BNO055_SetMagOffsets(s16_t* mag_bias){
  
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_LSB, (s16_t)mag_bias[0] & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_MSB, ((s16_t)mag_bias[0] >> 8) & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_LSB, (s16_t)mag_bias[1] & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_MSB, ((s16_t)mag_bias[1] >> 8) & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_LSB, (s16_t)mag_bias[2] & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_MSB, ((s16_t)mag_bias[2] >> 8) & 0xFF);
}

/*
* Function to set Accelometer radius by pre known values for fast calibration
* input parameter: s32_t variable that holds the radius value
*/
void BNO055_SetAccRadius(s32_t accel_radius){
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_RADIUS_LSB, (s16_t)accel_radius & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_RADIUS_MSB, ((s16_t)accel_radius >> 8) & 0xFF);
}
/*
* Function to Get Accelometer radius to be used for fast calibration (must be called after FULL_CALIBRATED)
* output parameter: s16_t variable that holds the radius value of accelometer
*/
s16_t BNO055_GetAccRadius(){
  s8_t low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_RADIUS_LSB);
  s8_t high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_RADIUS_MSB);
  return ((low & 0xFF)| (high<<8));
}
/*
* Function to set Magnetometer radius by pre known values for fast calibration 
* input parameter: s32_t variable that holds the radius value
*/
void BNO055_SetMagRadius(s32_t mag_radius){
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_LSB, (s16_t)mag_radius & 0xFF);
  BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_MSB, ((s16_t)mag_radius >> 8) & 0xFF);
}
/*
* Function to Get Magnetometer radius to be used for fast calibration (must be called after FULL_CALIBRATED)
* output parameter: s16_t variable that holds the radius value of Magnetometer
*/
s16_t BNO055_GetMagRadius(){
  s8_t low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_LSB);
  s8_t high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_MSB);
  return ((low & 0xFF)| (high<<8));
}

/*Function to set the calibration offsets and radius of all sensors together with saved value 
*save value must be saved after a FULL_CALIBRATED mode and be loaded into regs after every bootup for fast calibration
*inputs ST_BIAS_t that holds offsets and radius     (see BNO055.h for definition)*
*
*/
/*
void BNO055_SetCalibratioProfile(ST_BIAS_t bias){
  
    BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
    BNO055_SetAccOffsets(bias.ACCEL_OFFSET);
    BNO055_SetGyroOffsets(bias.GYRO_OFFSET);
    BNO055_SetMagOffsets(bias.MAG_OFFSET);
    BNO055_SetMagRadius(bias.MAG_RADIUS);
    BNO055_SetAccRadius(bias.ACCEL_RADIUS);
    BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, NDOF);
    
}*/
/*
*Function to Test the sensors see if they fail in hardware or not
*return EN_FAIL_t of the failed sensor (see BNO055.h for definition)
*   return 
*/
EN_FAIL_t BNO055_SelfTest(){
  u8_t selftest = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ST_RESULT);  
  if(!(selftest & 0x01)) {

    return ACCELOMETER_FAIL;                /*acc fails*/
  }
  if(!(selftest & 0x02)) {
    return MAGNETOMETER_FAIL;               /*magnetometer fails*/
  }
  if(!(selftest & 0x04)) {
    return GYROSCOPE_FAIL;              /*gyroscope fails*/
  }
  if(!(selftest & 0x08)) {
    return SYSTEM_FAIL;              /*system fails*/
  }

  return BNO055_SUCCESS;
}
