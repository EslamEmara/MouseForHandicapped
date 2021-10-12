//-------- the  new function that was added ---------------------

u8_t App_GetImuGradient(void)
{
  s16_t absolute_gradient[3]; // current_reading - reference_point
  //-- get current imu reading
  BNO055_ReadEulerAngles(current_reading);
  //-- compare this reading to calibration point to know imu (head) gradient
  absolute_gradient[0] = current_reading[0] - reference_angles[0];
  absolute_gradient[1] = current_reading[1] - reference_angles[1];
  absolute_gradient[2] = current_reading[2] - reference_angles[2];
  //-- decide depending on calculations to which direction mouse should move
  // get the largest angle of them (sign isn't considered)
  u8_t angle_name = App_GetLargestAngle(absolute_gradient[0],absolute_gradient[1],absolute_gradient[2]);
  
  // change period to set cursor speed 
	switch (absolute_gradient[angle_name-1])
	{
		// 20 -> threshold
		case 20 ... 40:
			cursor_speed = 10;
			break;
		case 41 ... 60:
			cursor_speed = 25;
			break;
		default: // larger than 60
			cursor_speed = 60;
			break;
	}
  
  // take action on mouse according to angle
	switch(angle_name)
	{
		// head is turned around X-axis
		case ROLL:
			// positive angle > threshold?
			if(absolute_gradient[0] >= THRESHOLD_X && RIGHT_CLICK_FLAG)
			{ 
				// disable flag to stop sending this signal multiple times
				RIGHT_CLICK_FLAG = DISABLED;
				// small angle (<25) -> single right click
				if (absolute_gradient[angle_name-1] < 25)
				{
					return RIGHT_CLICK;
				}
				// larger angle -> double right click
				 return DOUBLE_RIGHT_CLICK;
			}
			// negative angle > threshold?
			else if ( (-1*absolute_gradient[angle_name-1]) >= THRESHOLD_X && LEFT_CLICK_FLAG)
			{
				// disable flag to stop sending this signal multiple times
				 LEFT_CLICK_FLAG = DISABLED;
				 return LEFT_CLICK; 
			}
			break;
		// head is turned around Y-axis
		case PITCH:
		// enable flags so the signal can be sent again
			if(absolute_gradient[angle_name-1] >= THRESHOLD_Y){ RIGHT_CLICK_FLAG = ENABLED; RIGHT_CLICK_FLAG = ENABLED; return UP; }
			else if ( (-1*absolute_gradient[angle_name-1]) >= THRESHOLD_Y ){ RIGHT_CLICK_FLAG = ENABLED; RIGHT_CLICK_FLAG = ENABLED; return DOWN; }
			break;
		// head is turned around Z-axis
		case YAW:
		// enable flags so the signal can be sent again
			if(absolute_gradient[angle_name-1] >= THRESHOLD_Z){RIGHT_CLICK_FLAG = ENABLED; RIGHT_CLICK_FLAG = ENABLED; return RIGHT; }
			else if ( (-1*absolute_gradient[angle_name-1]) >= THRESHOLD_Z ){RIGHT_CLICK_FLAG = ENABLED; RIGHT_CLICK_FLAG = ENABLED; return LEFT; }
			break;
	}
	//-- no head motion 
	return NOTHING;
}

//--------------- The Function that was in the code -------------------

u8_t App_GetImuGradient(void)
{
  s16_t absolute_gradient[3]; // current_reading - reference_point
  //-- get current imu reading
  BNO055_ReadEulerAngles(current_reading);
  //-- compare this reading to calibration point to know imu (head) gradient
  absolute_gradient[0] = current_reading[0] - reference_angles[0];
  absolute_gradient[1] = current_reading[1] - reference_angles[1];
  absolute_gradient[2] = current_reading[2] - reference_angles[2];
  //-- decide depending on calculations to which direction mouse should move
  // get the largest angle of them (sign isn't considered)
  u8_t angle_name = App_GetLargestAngle(absolute_gradient[0],absolute_gradient[1],absolute_gradient[2]);
  switch(angle_name)
  {
    // head is turned around X-axis
    case ROLL:
      // positive angle > threshold?
      if((absolute_gradient[0] >= THRESHOLD_X )){ return RIGHT_CLICK; }
      // negative angle > threshold?
      else if (( (-1*absolute_gradient[0]) >= THRESHOLD_X )){return LEFT_CLICK; }
      break;
    // head is turned around Y-axis
    case PITCH:
      if(absolute_gradient[1] >= THRESHOLD_Y){ return UP; }
      else if ( (-1*absolute_gradient[1]) >= THRESHOLD_Y ){ return DOWN; }
      break;
    // head is turned around Z-axis
    case YAW:
      if(absolute_gradient[2] >= THRESHOLD_Z){ return RIGHT; }
      else if ( (-1*absolute_gradient[2]) >= THRESHOLD_Z ){ return LEFT; }
      break;
  }
  //-- no head motion 
  
  return NOTHING;
}