import serial, time
import cv2
import numpy as np

cap = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
ser = serial.Serial('/dev/ttyUSB0', 9600)

def capture_video(cap, face_cascade, ser):

  while True:
    ret, frame = cap.read()
    # BLUE
    cv2.rectangle(frame, (frame.shape[1]//2, frame.shape[0]), (0, 0), (100, 0, 0), 3)
    # RED
    cv2.rectangle(frame, (frame.shape[1], frame.shape[0]), (frame.shape[1]//2, 0), (0, 0, 255), 3)
  
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # obtenenos las pociones de las caras
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    for (x, y, w, h) in faces:
      center = (x + w//2, y + h//2)
      radius = max(w, h)//2

      if(center[0] > frame.shape[1]//2):
        # RED
        cv2.circle(frame, center, radius, (0, 0, 255), 3)
        #serial_send(ser, 'B')
      else:
        # BLUE
        cv2.circle(frame, center, radius, (100, 0, 0), 3)
        #serial_send(ser, 'G')

    cv2.imshow('my_video', cv2.flip(frame, 1))

    if(cv2.waitKey(1)== ord('q')):
      print(frame.shape)
      print(frame.shape[1]//2)
      print(center)
      ser.close()
      break
  cap.release()
  cv2.destroyAllWindows()

def serial_send(ser, data):
  print(ser.name)
  time.sleep(1)
  ser.write(data.encode())


if __name__ == '__main__':
  capture_video(cap, face_cascade, ser)