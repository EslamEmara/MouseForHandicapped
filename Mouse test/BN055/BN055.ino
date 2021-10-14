
#include "BNO055.h"

//------- Flags Status ----------
#define ENABLED   1
#define DISABLED  0

#define THRESHOLD_X  20 // 10 angles
#define THRESHOLD_Y  20 // 10 angles
#define THRESHOLD_Z  20  // 10 angles

u8_t RIGHT_CLICK_FLAG = ENABLED;
u8_t LEFT_CLICK_FLAG = ENABLED;

u16_t cursor_speed = 0;

s16_t reference_angles[3] = {0,0,0};
s16_t current_reading[3] = {0,0,0};

/* Movements of Mouse */
#define UP         0
#define DOWN      1
#define LEFT      2
#define RIGHT       3
#define LEFT_CLICK    4
#define RIGHT_CLICK   5
#define DOUBLE_LEFT_CLICK 6
#define NOTHING     255

/* Angles */
#define ROLL   2
#define PITCH  3
#define YAW    1

/* Touch Sensor Status */
#define CONTACT     1
#define NOT_CONTACT   0

/* Calibration Status */
#define CALIBRATED    8
#define NOT_CALIBRATED  9

u8_t App_GetLargestAngle(s16_t value1,s16_t value2,s16_t value3)
{ // yaw roll pitch
  value1 = abs(value1);
  value2 = abs(value2);
  value3 = abs(value3);
  if(value1 > value2)
  {
    if(value1 > value3)   { return 1; }
    else          { return 3; }
  }
  else
  {
    if(value2 > value3)   { return 2; }
    else          { return 3; }
  }
}



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
      cursor_speed = 1;
      break;
    case 41 ... 60:
      cursor_speed = 2;
      break;
    case 61 ... 90: // larger than 60
      cursor_speed = 3;
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


void App_OrderMouse(u8_t order)
{/*
  switch(order)
  {
    // cursor speed is u16_t
    case LEFT:        Serial.print("LEFT"); Serial.println(cursor_speed);  break;
    case RIGHT:       Serial.print("RIGHT"); Serial.println(cursor_speed);   break;
    case UP:          Serial.print("UP"); Serial.println(cursor_speed);  break;
    case DOWN:        Serial.print("DOWN"); Serial.println(cursor_speed);  break;
    case LEFT_CLICK:  Serial.println("LCLICK");   break;
    case RIGHT_CLICK: Serial.println("RCLICK");   break;
    case DOUBLE_LEFT_CLICK:
              Serial.println("DLCLICK");
              break;
    case NOTHING:     Serial.println("STOP");   break;
  }*/
}

u8_t App_SetReference(){
  if (digitalRead(8) == HIGH){
    delay(2000);
    if (digitalRead(8) == HIGH){
      BNO055_ReadEulerAngles(reference_angles);       // -100 , -50 , 0
      return 1;
    }
  }
  return 0;
}

void App_Init()
{
  pinMode(8, INPUT);  
  Serial.begin(9600);
  if (BNO055_Init() == BNO055_SUCCESS){
    Serial.println("BNO055 init success");
  }
  delay(2000);
  while (1){
    if (App_SetReference() == 1){
      break;
    }
  }
}
void setup() {
    App_Init();
}
int16_t  angles[3] ={0,0,0};

void loop() {
  if (digitalRead(8) == HIGH)
    App_OrderMouse(App_GetImuGradient());
  else{
    while (1){
    if (App_SetReference() == 1){
      break;
    }
  }
  delay(200);
}
}
