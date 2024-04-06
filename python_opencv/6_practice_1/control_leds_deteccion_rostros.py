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
    cv2.rectangle(frame, (0, frame.shape[0]//2), (frame.shape[1]//2, 0), (100, 0, 0), 2)
    # RED
    cv2.rectangle(frame, (frame.shape[1], frame.shape[0]//2), (frame.shape[1]//2, 0), (0, 0, 255), 2)
    # GREEN
    cv2.rectangle(frame, (0, frame.shape[0]), (frame.shape[1]//2, frame.shape[0]//2), (0, 255, 0), 2)
    # color aleatorio
    cv2.rectangle(frame, (frame.shape[1]//2, frame.shape[0]//2), (frame.shape[1], frame.shape[0]), (120, 23, 0), 2)

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # obtenenos las posiciones de las caras
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    # Variables para determinar si hay rostros en ambos lados
    face_left_1 = False
    face_left_2 = False
    face_rigth_1 = False
    face_rigth_2 = False

    # recorrer las caras detectadas
    for (x, y, w, h) in faces:
      # x, y
      center = (x + w//2, y + h//2)
      radius = max(w, h)//2
      

      # Verificar si el centro del rostro está a la derecha o a la izquierda de la mitad del ancho del marco
      if center[0] > frame.shape[1]//2 and center[1] < frame.shape[0]//2:
        face_rigth_1 = True
        print('rigth_1')
        # GREEN
        draw_circle(frame, center, radius=radius, color=(0, 0, 255))
        serial_send(ser, 'G')
      if center[0] < frame.shape[1]//2 and center[1] < frame.shape[0]//2:
        face_left_1 = True
        print('left_1')
        # BLUE
        draw_circle(frame, center, radius=radius, color=(100, 0, 0))
        serial_send(ser, 'B')

      # cv2.putText(frame, 'Hola mundo', (x, y), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

      if center[0] > frame.shape[1]//2 and center[1] > frame.shape[0]//2:
        face_rigth_2 = True
        print('rigth_2')
        # RED
        draw_circle(frame, center, radius=radius, color=(100, 0, 0))
        serial_send(ser, 'R')
      if center[0] < frame.shape[1]//2 and center[1] > frame.shape[0]//2:
        face_left_2 = True
        print('left_2')
        # YELLOW
        draw_circle(frame, center, radius=radius, color=(100, 0, 0))
        serial_send(ser, 'Y')
      
      print(f'Center X: {center[0]}')
      print(f'Center y: {center[1]}')
      print(f'Shape X: {frame.shape[1]//2}')
      print(f'Shape Y: {frame.shape[0]//2}')

    # Enviar un 4 a través de la comunicación serial si hay rostros en los 4 lados
    if face_left_1 and face_rigth_1 and face_left_2 and face_rigth_2:
      serial_send(ser, '4')

    # cv2.imshow('my_video', frame)
    cv2.imshow('my_video', cv2.flip(frame, 1))

    if(cv2.waitKey(1)== ord('q')):
      serial_send(ser, '0')
      print(len(faces))
      ser.close()
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
  capture_video(cap, face_cascade, ser)
