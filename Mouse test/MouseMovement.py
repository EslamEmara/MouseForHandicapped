

import pyautogui
import serial
import time

arduino = serial.Serial('COM3',9600)
print("Arduino connected")
time.sleep(2)

while(True):

    order_data = arduino.readline()
    order_data = order_data.decode('UTF-8')
    print(order_data)
    
    speed_data = arduino.readline()
    speed_data = speed_data.decode('UTF-8')
    print(speed_data)
    
    if ("LEFT" in order_data):
        pyautogui.moveRel(-10, 0, duration = 0)
    elif ("RIGHT" in order_data):
        pyautogui.moveRel(10, 0, duration = 0)
    elif ("UP" in order_data):
        pyautogui.moveRel(0, -10, duration = 0)
    elif ("DOWN" in order_data):
        pyautogui.moveRel(0, 10, duration = 0)
    elif ("LCLICK" in order_data):
        pyautogui.click(pyautogui.position())
    elif ("RCLICK" in order_data):
        pyautogui.click(button='right')
        
    elif ("DLCLICK" in order_data):
        pyautogui.click(pyautogui.position())
        pyautogui.click(pyautogui.position())
        
    else:
        pass
