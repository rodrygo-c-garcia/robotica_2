import serial, time
import cv2

serial = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(1)
serial.write(b'A')
serial.close()
print(serial.name)
