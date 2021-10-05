




#include "APP/App_interface.h"

int main()
{
	/* Init application */
	App_Init();
	
	while(1)
	{
		/* Check touch sensor state */
		uint8_t state = App_GetTouchSensorStatus();
		
		if(state == CONTACT)
		{
			// Get calibration point from imu
			uint8_t calibration_status = App_GetCalibStatus();
			
			// loop till sensors calibrated
			while(calibration_status == NOT_CALIBRATED)
			{
				calibration_status = App_GetCalibStatus();
			}
			
			App_GetImuCalibPoint(angles);
			// Get current gradient of imu (required mouse motion direction)
			uint8_t motion_direction = App_GetImuGradDirection();
			// move mouse
			App_OrderMouse(motion_direction);
		}
			
	}
}