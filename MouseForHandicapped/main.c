




#include "APP/App_interface.h"

int main()
{
	/* Init application */
	App_Init();
	
	while(1)
	{
		DBG1(0x02, 0, 0);   /* debug output: main loop iterates */
		wdt_reset();
		usbPoll();
		if(usbInterruptIsReady()){
		/* called after every poll of the interrupt endpoint */
	    advanceCircleByFixedAngle();
	    DBG1(0x03, 0, 0);   /* debug output: interrupt report prepared */
	    usbSetInterrupt((void *)&reportBuffer, sizeof(reportBuffer));
    }
		/* Check touch sensor state */
		uint8_t state = App_GetTouchSensorStatus();
		
		if(state == CONTACT)
		{
			uint8_t motion_direction = App_GetImuGradDirection();
			App_OrderMouse(motion_direction);
		}
			
	}
}