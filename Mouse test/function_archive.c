//-------- latest Version 02 ---------------------

u8_t App_GetImuGradient(void)
{
  s16_t absolute_gradient[3]; // current_reading - reference_point
  //-- get current imu reading
  BNO055_ReadEulerAngles(current_reading);
  //-- compare this reading to calibration point to know imu (head) gradient
  absolute_gradient[0] = current_reading[0] - reference_angles[0];   
  if (absolute_gradient[0] < 0 ){
     absolute_gradient[0] +=360;
  }
  absolute_gradient[1] = current_reading[1] - reference_angles[1]; 
    if (absolute_gradient[1] < 0 ){
     absolute_gradient[1] +=360;
  }   
  absolute_gradient[2] = current_reading[2] - reference_angles[2]; 
    if (absolute_gradient[2] < 0 ){
     absolute_gradient[2] +=360;
  }
  Serial.println(absolute_gradient[0]);
  Serial.println(absolute_gradient[1]);
  Serial.println(absolute_gradient[2]);
  Serial.println("__________________________");
  //-- decide depending on calculations to which direction mouse should move
  // get the largest angle of them (sign isn't considered)
  u8_t angle_name = App_GetLargestAngle(absolute_gradient[0],absolute_gradient[1],absolute_gradient[2]);
  
  // change period to set cursor speed 
	switch (absolute_gradient[angle_name-1])
	{
		// 20 -> threshold
		case 20 ... 40:
		case 360-20 ... 360-40:
			cursor_speed = 1;
			break;
		case 41 ... 60:
		case 360-41 ... 360-60:
			cursor_speed = 2;
			break;
		case 61 ... 89: // larger than 60
		case 360-61 ... 360-89:
			cursor_speed = 3;
			break;
		default:
			cursor_speed = 0;
			break;
	}
  
  // take action on mouse according to angle
	switch(angle_name)
	{
		// head is turned around X-axis (RIGHT_CLICK, LEFT_CLICK, DOUBLE_LEFT_CLICK)
		case ROLL:
			// angle > threshold?
			// angle range [20:180]
			if(absolute_gradient[angle_name-1] >= THRESHOLD_X && absolute_gradient[angle_name-1] < 180 && RIGHT_CLICK_FLAG)
			{ 
				// disable flag to stop sending this signal multiple times
				RIGHT_CLICK_FLAG = DISABLED;
				// enable left click
				LEFT_CLICK_FLAG = ENABLED;
				// enable double left flag
				DL_FLAG = ENABLED;
				return RIGHT_CLICK;
				
			}
			// angle < 360-threshold?
			else if ( (absolute_gradient[angle_name-1]) <= (360-THRESHOLD_X) && (LEFT_CLICK_FLAG || DL_FLAG) )
			{

				// enable right click
				RIGHT_CLICK_FLAG = ENABLED;
				// angle in range [320:360] -> left click
				if (absolute_gradient[angle_name-1] > 360-(THRESHOLD_X+20))
				{
					// disable flag to stop sending this signal multiple times
					LEFT_CLICK_FLAG = DISABLED;
					// enable double left flag
					DL_FLAG = ENABLED;
					 return LEFT_CLICK;
				}
				// angle in range [180:320] -> double left click
				else if(absolute_gradient[angle_name-1] > 180)
					DL_FLAG = DISABLED;
					LEFT_CLICK_FLAG = ENABLED;
					return DOUBLE_LEFT_CLICK;
			}
			break;
		// head is turned around Y-axis (UP, DOWN)
		case PITCH:
			// enable flags so the signal can be sent again
			// angle range [20:180]
			if(absolute_gradient[angle_name-1] >= THRESHOLD_Y && absolute_gradient[angle_name-1] < 180)
			{ RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; DL_FLAG = ENABLED; return UP; }
			// angle range [180:360]
			else if ( absolute_gradient[angle_name-1] > 180 && absolute_gradient[angle_name-1] < 360 )
			{ RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; DL_FLAG = ENABLED; return DOWN; }
			break;
		// head is turned around Z-axis (Left, Right)
		case YAW:
			// enable flags so the signal can be sent again
			if(absolute_gradient[angle_name-1] >= THRESHOLD_Z && absolute_gradient[angle_name-1] < 180)
			{RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; DL_FLAG = ENABLED; return RIGHT; }
			else if ( absolute_gradient[angle_name-1] > 180 && absolute_gradient[angle_name-1] < 360 )
			{RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; DL_FLAG = ENABLED; return LEFT; }
			break;
	}
	//-- no head motion 
	RIGHT_CLICK_FLAG = ENABLED;
	LEFT_CLICK_FLAG = ENABLED;
	DL_FLAG = ENABLED;
	return NOTHING;
}







//---------- Version 01 --------------------

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
    case 61 ... 90: // larger than 60
      cursor_speed = 60;
      break;
    default:
      // do nothing
      break;
  }
  
  // take action on mouse according to angle
  switch(angle_name)
  {
    // head is turned around X-axis (RIGHT_CLICK, LEFT_CLICK, DOUBLE_LEFT_CLICK)
    case ROLL:
      // positive angle > threshold?
      if(absolute_gradient[angle_name-1] >= THRESHOLD_X && RIGHT_CLICK_FLAG)
      { 
        // disable flag to stop sending this signal multiple times
        RIGHT_CLICK_FLAG = DISABLED;
        // enable left click
        LEFT_CLICK_FLAG = ENABLED;
        
        return RIGHT_CLICK;
        
      }
      // negative angle > threshold?
      else if ( (-1*absolute_gradient[angle_name-1]) >= THRESHOLD_X && LEFT_CLICK_FLAG)
      {
        // disable flag to stop sending this signal multiple times
        LEFT_CLICK_FLAG = DISABLED;
        // enable right click
        RIGHT_CLICK_FLAG = ENABLED;
        if (absolute_gradient[angle_name-1] < 30)
        {
           return LEFT_CLICK; 
        }
         // larger angle -> double left click
         return DOUBLE_LEFT_CLICK;
      }
      break;
    // head is turned around Y-axis (UP, DOWN)
    case PITCH:
    // enable flags so the signal can be sent again
      if(absolute_gradient[angle_name-1] >= THRESHOLD_Y){ RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; return UP; }
      else if ( (-1*absolute_gradient[angle_name-1]) >= THRESHOLD_Y ){ RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; return DOWN; }
      break;
    // head is turned around Z-axis (Left, Right)
    case YAW:
    // enable flags so the signal can be sent again
      if(absolute_gradient[angle_name-1] >= THRESHOLD_Z){RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; return RIGHT; }
      else if ( (-1*absolute_gradient[angle_name-1]) >= THRESHOLD_Z ){RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; return LEFT; }
      break;
  }
  //-- no head motion 
  return NOTHING;
}


//--------------- Version 00 -------------------

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