

import pyautogui
import serial
import time

pyautogui.PAUSE = 0
pyautogui.FAILSAFE = True

arduino = serial.Serial('COM3', 4800)
print("Arduino connected")
time.sleep(2)
def get_digits(text):
    c = ""
    for i in text:
        if i.isdigit():
            c += i
    return c

while(True):
    try:
        order_data = arduino.readline()
        order_data = order_data.decode('UTF-8')
        print(order_data)

        if ("LEFT" in order_data):
            pyautogui.moveRel(-1*int(get_digits(order_data)), 0, duration=0)
        elif ("RIGHT" in order_data):
            pyautogui.moveRel(int(get_digits(order_data)), 0, duration=0)
        elif ("UP" in order_data):
            pyautogui.moveRel(0, -1*int(get_digits(order_data)), duration=0)
        elif ("DOWN" in order_data):
            pyautogui.moveRel(0, int(get_digits(order_data)), duration=0)
        elif ("LCLICK" in order_data):
            pyautogui.click(pyautogui.position())
        elif ("RCLICK" in order_data):
            pyautogui.click(button='right')

        elif ("DLCLICK" in order_data):
            pyautogui.click(clicks=2)
            
        else:
            pass
    except:
        pass

