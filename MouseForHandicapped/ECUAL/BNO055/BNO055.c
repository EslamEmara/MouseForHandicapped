/*
 * BNO055.c
 *
 * Created: 10/2/2021 4:08:32 PM
 *  Author: Omar & Eslam
 */ 
#include "BNO055.h"

void BNO055_Init()
{
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
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
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, OP_MODE  );
	
}


void BNO055_WriteByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
	I2C_Master_Start(address);  // Initialize the Tx buffer
	I2C_Master_Write(subAddress);      // Put slave register address in Tx buffer
	I2C_Master_Write(data);                 // Put data in Tx buffer
	I2C_Repeated_Start(address);           // Send the Tx buffer
}

uint8_t BNO055_ReadByte(uint8_t address, uint8_t subAddress)
{
	uint8_t data; // `data` will store the register data
	I2C_Master_Start(address);         // Initialize the Tx buffer
	I2C_Master_Write(subAddress);	                 // Put slave register address in Tx buffer
	I2C_Repeated_Start(address);        // Send the Tx buffer, but send a restart to keep connection alive
	data =I2C_Read_Ack();                      // Fill Rx buffer with result
	return data;                             // Return data read from slave register
}
void BNO055_ReadBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * data)
{
	uint8_t data_count = 0;
	I2C_Master_Start(address); 
	I2C_Master_Write(subAddress);           
	I2C_Repeated_Start(address) ;

	for (data_count= 0 ; data_count < count ;++data_count){
		data[data_count] =I2C_Read_Ack();
	}       
	data[count] = I2C_Read_Nack();
}
EN_CALIBRATION_t BNO055_GetCalibStat(EN_SENSOR_t sensor){
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

void BNO055_GetAccOffsets(int32_t* accel_bias){
	int8_t low = 0;
	int8_t high = 0;
	
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
void BNO055_SetGyroOffsets(int32_t* gyro_bias){
	
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_LSB, (int16_t)gyro_bias[0] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_MSB, ((int16_t)gyro_bias[0] >> 8) & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_LSB, (int16_t)gyro_bias[1] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_MSB, ((int16_t)gyro_bias[1] >> 8) & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_LSB, (int16_t)gyro_bias[2] & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_MSB, ((int16_t)gyro_bias[2] >> 8) & 0xFF);
}
void BNO055_GetGyroOffsets(int32_t* gyro_bias){
	int8_t low = 0;
	int8_t high = 0;
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

void BNO055_GetMagOffsets(int32_t* mag_bias){
	int8_t low = 0;
	int8_t high = 0;
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
int16_t BNO055_GetAccRadius(int32_t accel_radius){
	int8_t low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_RADIUS_LSB);
	int8_t high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ACC_RADIUS_MSB);
	return ((low & 0xFF)| (high<<8));
}

void BNO055_SetMagRadius(int32_t mag_radius){
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_LSB, (int16_t)mag_radius & 0xFF);
	BNO055_WriteByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_MSB, ((int16_t)mag_radius >> 8) & 0xFF);
}

int16_t BNO055_GetMagRadius(int32_t mag_radius){
	int8_t low = BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_LSB);
	int8_t high = BNO055_ReadByte(BNO055_ADDRESS, BNO055_MAG_RADIUS_MSB);
	return ((low & 0xFF)| (high<<8));
}


void BNO055_SetCalibratioProfile(int32_t* accel_bias,int32_t* gyro_bias,int32_t* mag_bias,int32_t accel_radius,int32_t mag_radius){
	
	  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
	  BNO055_SetAccOffsets(accel_bias);
	  BNO055_SetGyroOffsets(gyro_bias);
	  BNO055_SetMagOffsets(mag_bias);
	  BNO055_SetMagRadius(mag_radius);
	  BNO055_SetAccRadius(accel_radius);
	  BNO055_WriteByte(BNO055_ADDRESS, BNO055_OPR_MODE, NDOF);
	  
}
int8_t BNO055_SelfTest(){
	uint8_t selftest = BNO055_ReadByte(BNO055_ADDRESS, BNO055_ST_RESULT);
	uint8_t test = 0;
	
	if(selftest & 0x01) {
		test++;
		} else {
		return ACCELOMETER_FAIL;                /*acc fails*/
	}
	if(selftest & 0x02) {
		test++;
		} else {
		return MAGNETOMETER_FAIL;               /*magnetometer fails*/
	}
	if(selftest & 0x04) {
		test++;
		} else {
		return GYROSCOPE_FAIL;              /*gyroscope fails*/
	}
	if(selftest & 0x08) {
		test++;
		} else {
		return SYSTEM_FAIL;              /*system fails*/
	}

	return test;
}

