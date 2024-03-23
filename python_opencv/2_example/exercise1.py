import cv2
import os
import numpy as np

path = os.path.join('..', 'img', 'modify_paisaje.jpg')
# con -1 dimension 4, en imagenes png
# RGBO
# O -> opacity

img_original = cv2.imread(path, 1)

def show_image(img):
    # creamos una ventana para mostrar la imagen
    cv2.imshow('Windows', img)
    # tiempo que se muestra la imagen
    cv2.waitKey(0)
    # cerramos la ventana y liberamos los recursos
    cv2.destroyAllWindows()

def resize_img(image):
    width = 300
    height = 300
    scale = 0.5
    return cv2.resize(image, (0, 0), fx=scale, fy=scale)

def rotate_img(image):
    # cv2.ROTATE_90_CLOCKWISE: Rota la imagen 90 grados en sentido horario.
    # cv2.ROTATE_180: Rota la imagen 180 grados (o la voltea).
    # cv2.ROTATE_90_COUNTERCLOCKWISE: Rota la imagen 90 grados en sentido antihorario (o 270 grados en sentido horario).
    return cv2.rotate(image, cv2.ROTATE_90_CLOCKWISE)

def save_image(img):
    cv2.imwrite('../img/modify_paisaje.jpg', resize_img(img))
    print('Image saved')
    path = os.path.join('..', 'img', 'modify_paisaje.jpg')
    return cv2.imread(path, 1)

if __name__ == '__main__':
    # show_image(img_original)
    # print(img_original)
    # print(type(img_original))
    # print(img_original.shape)
    # print(img_original[0, 0])
    # imprime la fila de la matriz
    # print(img_original[3])
    # de la fila 4 mostramos rango de pixels
    # print(img_original[3][20:50])
    
    """  p = img_original[200:399, 250:399]
    print(f'P Shape: {p.shape}')
    img_original[0:199, 0:149] = p
    print(f'M Shape: {img_original[0:199, 0:149].shape}')
    show_image(img_original)
    """

    #-------------
    # show_image(save_image(resize_img(img_original)))
    show_image(img_original)
    print(img_original.shape)