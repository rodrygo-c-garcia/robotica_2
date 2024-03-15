# This is a sample Python script.
import cv2
import os
import numpy as np

# read image whit opencv
path = os.path.join('img', 'paisaje.jpg')
# 0 ==> escala de grises
# 1 ==> color RGB, mantiene las transpariencias
# -1 ==> color RGB, NO mantiene las transpariencias
imgOriginal = cv2.imread(path, 0)

def showImage(img):
    # show image
    cv2.imshow('Windows', img)
    # time show
    cv2.waitKey(0)
    # delete windows and resources
    cv2.destroyAllWindows()

def resizeImage(img):
    # fx = 0.5 --> reduce a la mitad la x
    # fy = 0.5 --> reduce a la mitad la y
    imgResize = cv2.resize(img, (0, 0), fx=0.3, fy=0.3)
    return imgResize

def rotateImage(img):
    imageRotate = cv2.rotate(img, cv2.ROTATE_180)
    return resizeImage(imageRotate)

def saveImage(img):
    cv2.imwrite('img/imgModify.jpg', resizeImage(img))

def modifyImage(img):
    cv2.imwrite('img/lab.jpg', resizeImage(img))

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    # modifyImage(imgOriginal)
    showImage(cv2.imread('img/lab.jpg', 1))


