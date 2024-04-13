import cv2
import numpy as np

cap = cv2.VideoCapture("http://10.44.147.226:8080/video")
# cap = cv2.VideoCapture("/dev/media0")


#cap = cv2.VideoCapture(0)

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye.xml')

print(type(face_cascade))
print(type(eye_cascade))

while True:
  ret, frame = cap.read()
  # convertimos a gris
  gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

  # obtenenos las pociones de las caras
  faces = face_cascade.detectMultiScale(gray, 1.3, 5)
  # iteramos las detecciones
  for (x, y, w, h) in faces:
    cv2.rectangle(frame, (x, y), (x+w, y+h), (200, 0, 255), 3)
    face_gray = gray[y:y+h, x:x+w]
    # area de interes 
    face_color = frame[y:y+h, x:x+w]
    # obtenemos los valores de los resutados 
    eyes = eye_cascade.detectMultiScale(face_gray)
    for(ex, ey, ew, eh) in eyes:
      cv2.rectangle(face_color, (ex, ey), (ex+ew, ey+eh), (0, 255, 0), 2)

  cv2.imshow('my_video', cv2.flip(frame, 1))

  if(cv2.waitKey(1)== ord('q')):
    break

# para la grabacion del video
cap.release()
cv2.destroyAllWindows()

# ver alto y ancho del video, ver el punto especifico de la cara
# que la led se prenda de la mitad del video hacia la derecha
# y que se prenda otro led de la mitad del video hacia la izquierda

# todo serial