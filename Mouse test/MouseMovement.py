

import pyautogui
import serial
import time

arduino = serial.Serial('COM3',9600)
print("Arduino connected")
time.sleep(2)

while(True):

    data = arduino.readline()
    data = data.decode('UTF-8')
    print(data)

    if ("LEFT" in data):
        pyautogui.moveRel(-10, 0, duration = 0)
    if ("RIGHT" in data):
        pyautogui.moveRel(10, 0, duration = 0)
    if ("UP" in data):
        pyautogui.moveRel(0, -10, duration = 0)
    if ("DOWN" in data):
        pyautogui.moveRel(0, 10, duration = 0)
    if ("LCLICK" in data):
        pyautogui.click(pyautogui.position())
    if ("RCLICK" in data):
        pyautogui.click(button='right')
