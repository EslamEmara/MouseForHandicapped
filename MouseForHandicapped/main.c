

#include "MCAL/DIO/TypeDefs.h"
#include "APP/App_interface.h"

extern report_t reportBuffer;

int main()
{
	/* Init application */
	App_Init();
	
	while(1)
	{
		// Ensure usb is always up
		DBG1(0x02, 0, 0);   /* debug output: main loop iterates */
		wdt_reset();
		usbPoll();
		if(usbInterruptIsReady())
		{
		/* called after every poll of the interrupt endpoint */
	    advanceCircleByFixedAngle();
	    DBG1(0x03, 0, 0);   /* debug output: interrupt report prepared */
	    usbSetInterrupt((void *)&reportBuffer, sizeof(reportBuffer));
		}
		//------------------------------------------
		// START LOGIC
		/* Check touch sensor state */
		u8_t state = App_GetTouchSensorState();
		
		if(state == CONTACT)
		{
			// Get calibration point from imu
			App_GetImuCalibPoint(angles);
			
			
			// Get current gradient of imu (required mouse motion direction)
			u8_t motion_direction = App_GetImuGradient();
			// move mouse
			App_OrderMouse(motion_direction);
		}
	}
	return 0;
}