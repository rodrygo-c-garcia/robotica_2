import serial, time
import cv2
import numpy as np

cap = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

def capture_video(cap, face_cascade):

  while True:
    ret, frame = cap.read()
    
    width = frame.shape[1]
    height = frame.shape[0]
    
    part_1W = width//3
    part_2W = width//3*2
    
    part_1H = height//3
    part_2H = height//3*2
    
    # LEFT
    cv2.rectangle(frame, (0, height), (part_1W, 0), (100, 0, 0), 2)
    # RIGHT
    cv2.rectangle(frame, (width, 0), (part_2W, height), (0, 0, 255), 2)

    # TOP
    cv2.rectangle(frame, (part_1W, 0), (part_2W, part_1H), (0, 255, 0), 2)

    # CENTER
    cv2.rectangle(frame, (part_1W, part_1H), (part_2W, part_2H), (110, 100, 0), 2)
    
    # LOW
    cv2.rectangle(frame, (part_1W, part_2H), (part_2W, height), (10, 0, 30), 2)

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # obtenenos las posiciones de las caras
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)


    # recorrer las caras detectadas
    for (x, y, w, h) in faces:
      # x, y
      center = (x + w//2, y + h//2)
      radius = max(w, h)//2
      

      # Verificar si el centro del rostro está a la derecha o a la izquierda de la mitad del ancho del marco
      if center[0] < part_1W:
        print('LEFT')
        # GREEN
        draw_circle(frame, center, radius=radius, color=(0, 0, 255))
        
      if center[0] > part_2W:
        print('RIGHT')
        # BLUE
        draw_circle(frame, center, radius=radius, color=(100, 0, 0))

      if center[0] > part_1W and center[0] < part_2W and center[1] < part_1H:
        print('TOP')
        # RED
        draw_circle(frame, center, radius=radius, color=(100, 0, 0))
      
      if center[0] > part_1W and center[0] < part_2W and center[1] > part_1H and center[1] < part_2H:
        print('CENTER')
        # YELLOW
        draw_circle(frame, center, radius=radius, color=(100, 0, 0))
      
      if center[0] > part_1W and center[0] < part_2W and center[1] > part_2H:
        print('LOW')
        draw_circle(frame, center, radius=radius, color=(100, 0, 0))
        
      print(f'Center X: {center[0]}')
      print(f'Center y: {center[1]}')

    #cv2.imshow('my_video', frame)
    cv2.imshow('my_video', cv2.flip(frame, 1))

    if(cv2.waitKey(1)== ord('q')):
      #serial_send(ser, '0')
      print(len(faces))
      #ser.close()
      break

  cap.release()
  cv2.destroyAllWindows()

def serial_send(ser, data):
  # print('Data: ' + data)
  ser.write(data.encode())

def draw_circle(frame, center, radius, color):
  cv2.circle(frame, center, radius, color, 3)
  # Dibuja un punto en la posición del centro
  cv2.circle(frame, center, radius=3, color=color, thickness=-1)

if __name__ == '__main__':
  capture_video(cap, face_cascade)
