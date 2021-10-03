/*
 * BNO055.c
 *
 * Created: 10/2/2021 4:08:32 PM
 *  Author: Omar
 */ 
#include "BNO055.h"

void BNO055_Init()
{
	
}

// I2C read/write functions for the BNO055 sensor

void BNO055_WriteByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
	I2C_Master_Start(address);  // Initialize the Tx buffer
	I2C_Master_Write(subAddress);      // Put slave register address in Tx buffer
	I2C_Master_Write(data);                 // Put data in Tx buffer
	I2C_Repeated_Start(subAddress);           // Send the Tx buffer
}

uint8_t BNO055_ReadByte(uint8_t address, uint8_t subAddress)
{
	uint8_t data; // `data` will store the register data
	I2C_Master_Start(address);         // Initialize the Tx buffer
	I2C_Master_Write(subAddress);	                 // Put slave register address in Tx buffer
	I2C_Repeated_Start();        // Send the Tx buffer, but send a restart to keep connection alive
	data =I2C_Read_Ack();                      // Fill Rx buffer with result
	return data;                             // Return data read from slave register
}
void BNO055_ReadBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * data)
{
	I2C_Master_Start(address); 
	I2C_Master_Write(subAddress);           
	I2C_Repeated_Start 
	uint8_t data_count = 0;
	for (data_count= 0 ; data_count < count ;++data_count){
		data[data_count] =I2C_Read_Ack();
	}       
	data[count] = I2C_Read_Nack();
}
uint8_t BNO055_GetCalibStat(EN_SENSOR_t sensor){
	 uint8_t calstat = BNO055_ReadByte(BNO055_ADDRESS, BNO055_CALIB_STAT);
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

void BNO055_ReadAcc(int16_t * destination)
{
	uint8_t rawData[6];  // x/y/z accel register data stored here
	BNO055_ReadBytes(BNO055_ADDRESS, BNO055_ACC_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers into data array
	destination[0] = ((int16_t)rawData[1] << 8) | rawData[0] ;      // Turn the MSB and LSB into a signed 16-bit value
	destination[1] = ((int16_t)rawData[3] << 8) | rawData[2] ;
	destination[2] = ((int16_t)rawData[5] << 8) | rawData[4] ;
}


void BNO055_ReadGyro(int16_t * destination)
{
	uint8_t rawData[6];  // x/y/z gyro register data stored here
	BNO055_ReadBytes(BNO055_ADDRESS, BNO055_GYR_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
	destination[0] = ((int16_t)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
	destination[1] = ((int16_t)rawData[3] << 8) | rawData[2] ;
	destination[2] = ((int16_t)rawData[5] << 8) | rawData[4] ;
}

void BNO055_ReadMag(int16_t * destination)
{
	uint8_t rawData[6];  // x/y/z gyro register data stored here
	BNO055_ReadBytes(BNO055_ADDRESS, BNO055_MAG_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
	destination[0] = ((int16_t)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
	destination[1] = ((int16_t)rawData[3] << 8) | rawData[2] ;
	destination[2] = ((int16_t)rawData[5] << 8) | rawData[4] ;
}
void BNO055_ReadEulerAngles(int16_t * destination)
{
	uint8_t rawData[6];  // x/y/z gyro register data stored here
	BNO055_ReadBytes(BNO055_ADDRESS, BNO055_EUL_HEADING_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
	destination[0] = ((int16_t)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
	destination[1] = ((int16_t)rawData[3] << 8) | rawData[2] ;
	destination[2] = ((int16_t)rawData[5] << 8) | rawData[4] ;
}

void BNO055_SetAccOffsets(int32_t* accel_bias){
	
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_LSB, (int16_t)accel_bias[0] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_MSB, ((int16_t)accel_bias[0] >> 8) & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_LSB, (int16_t)accel_bias[1] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_MSB, ((int16_t)accel_bias[1] >> 8) & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_LSB, (int16_t)accel_bias[2] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_MSB, ((int16_t)accel_bias[2] >> 8) & 0xFF);
}
void BNO055_SetGyroOffsets(int32_t* gyro_bias){
	
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_LSB, (int16_t)gyro_bias[0] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_MSB, ((int16_t)gyro_bias[0] >> 8) & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_LSB, (int16_t)gyro_bias[1] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_MSB, ((int16_t)gyro_bias[1] >> 8) & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_LSB, (int16_t)gyro_bias[2] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_MSB, ((int16_t)gyro_bias[2] >> 8) & 0xFF);
}
void BNO055_SetMagOffsets(int32_t* mag_bias){
	
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_LSB, (int16_t)mag_bias[0] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_MSB, ((int16_t)mag_bias[0] >> 8) & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_LSB, (int16_t)mag_bias[1] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_MSB, ((int16_t)mag_bias[1] >> 8) & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_LSB, (int16_t)mag_bias[2] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_MSB, ((int16_t)mag_bias[2] >> 8) & 0xFF);
}
void BNO055_SetAccRadius(int32_t accel_radius){
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_RADIUS_LSB, (int16_t)accel_radius & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_ACC_RADIUS_MSB, ((int16_t)accel_radius >> 8) & 0xFF);
}
void BNO055_SetMagRadius(int32_t mag_radius){
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_LSB, (int16_t)mag_radius & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_MSB, ((int16_t)mag_radius >> 8) & 0xFF);
}
void BNO055_SetCalibratioProfile(int32_t* accel_bias,int32_t* gyro_bias,int32_t* mag_bias,int32_t accel_radius,int32_t mag_radius){
	
	  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
	  BNO055_SetAccOffsets(accel_bias);
	  BNO055_SetGyroOffsets(gyro_bias);
	  BNO055_SetMagOffsets(mag_bias);
	  BNO055_SetMagRadius(mag_radius);
	  BNO055_SetAccRadius(accel_radius);
	  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, OPRMode);
	  
}
