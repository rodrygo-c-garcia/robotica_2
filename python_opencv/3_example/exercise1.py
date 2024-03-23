# Videos OpenCV
import cv2
import os
import numpy as np

# capture almacena los frames del video
capture = cv2.VideoCapture(0)
while True:
  # ret = false o true (si leyo bien el frame)
  # frame se guarda la imagen
  ret, frame = capture.read() 

  #cambiamos el color a escala de grises
  gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

  cv2.imshow('my_video', frame)

  # si presionamos 'q' salimos del ciclo
  if cv2.waitKey(1) == ord('q'):
    print(f'frame.shape: {frame.shape}')
    print(f'gray.shape: {gray.shape}')
    break

# para la grabacion del video
capture.release()
cv2.destroyAllWindows()