




#include "App_interface.h"

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
			uint8_t motion_direction = App_GetImuGradDirection();
			App_OrderMouse(motion_direction);
		}
			
	}
}