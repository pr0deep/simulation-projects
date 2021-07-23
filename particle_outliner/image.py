import numpy as np 
import cv2
import variables

img = cv2.imread('dog.jpg',cv2.IMREAD_GRAYSCALE)
_,img2 = cv2.threshold(img,150,255,cv2.THRESH_BINARY)
img2 = cv2.resize(img2,(200,200))
preprocessed = []

for j in range(len(img2)):
    for i in range(len(img2[0])):
        if not img2[j][i]:
            preprocessed.append((i+variables.offset_image,j+variables.offset_image))
cv2.imshow("win",img2)
#cv2.waitKey(0)