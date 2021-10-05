


#define APP_PRIVATE_H_
#ifndef APP_PRIVATE_H_

/*****
 * Description: Get the largest value regardless the signs
 * args: value1 -> (int16_t)
 *		 value2 -> (int16_t)
 *		 value3 -> (int16_t)
 * return: index of the largest value (1 or 2 or 3) -> uint8_t
 * Ex: index = App_GetLargestAngle(54,21,100); -> index=3
 */
static uint8_t App_GetLargestAngle(int16_t value1,int16_t value2,int16_t value3);






#endif