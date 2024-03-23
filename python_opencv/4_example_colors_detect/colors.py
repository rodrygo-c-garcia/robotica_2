import cv2
import numpy as np

# BGR -- Video
# HSV -- matiz, saturacion y brillo
cap = cv2.VideoCapture(0)

while True:
  # ret = false o true (si leyo bien el frame)
  # frame se guarda la imagen
  ret, frame = cap.read()
  # convertimos el frame a hsv
  hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

  # minimo y maximo valor del color azul en HSV
  min_blue = np.array([160, 50, 50])
  max_blue = np.array([180, 255, 255])

  # creamos una mascara binaria. 1 pixel que este dentro del rango y 0 si no
  mask = cv2.inRange(hsv, min_blue, max_blue)
  # aplicamos la mascara a la imagen original
  result = cv2.bitwise_and(frame, frame, mask=mask)
  # show image
  cv2.imshow('my_video', cv2.flip(frame, 1)) 

  if cv2.waitKey(1) == ord('q'):
    print(f'frame.shape: {hsv.shape}')
    break

# para la grabacion del video
cap.release()
cv2.destroyAllWindows()