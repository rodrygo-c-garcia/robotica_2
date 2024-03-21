import numpy as np
import cv2

# creamos una imagen de ceros
img = np.zeros((512, 512, 3), np.uint8)
width, height, _ = img.shape

# color BGR 
cv2.line(img, (30, 10), (511, 511), (0, 0, 255), 5)

cv2.rectangle(img, (width//2, height//2), (511, 511), (0, 255, 0), 3)

def show_image(img):
    # creamos una ventana para mostrar la imagen
    cv2.imshow('Windows', img)
    # tiempo que se muestra la imagen
    cv2.waitKey(0)
    # cerramos la ventana y liberamos los recursos
    cv2.destroyAllWindows()

if __name__ == '__main__':
    show_image(img)