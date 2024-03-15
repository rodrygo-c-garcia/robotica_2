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
  # ancho y alto
  width = int(capture.get(cv2.CAP_PROP_FRAME_WIDTH))
  height = int(capture.get(cv2.CAP_PROP_FRAME_HEIGHT))

  # una imagen de puros zeros
  imagen = np.zeros(frame.shape, np.uint8)

  # el frame convertimos mas pequeno, a la mitad
  frame_small = cv2.resize(frame, (0, 0), fx=0.5, fy=0.5)

  imagen[:height//2, :width//2] = frame_small
  imagen[height//2:, :width//2] = frame_small
  imagen[:height//2, width//2:] = cv2.flip(frame_small, 1)
  imagen[height//2:, width//2:] = cv2.rotate(frame_small, cv2.ROTATE_180)

  cv2.imshow('my_video', cv2.flip(frame, 1))

  # si presionamos 'q' salimos del ciclo
  if cv2.waitKey(1) == ord('q'):
    break

# para la grabacion del video
capture.release()
cv2.destroyAllWindows()