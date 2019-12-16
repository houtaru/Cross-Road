import cv2
import sys

    img = cv2.imread(filename, cv2.IMREAD_UNCHANGED)
     
    print('Original Dimensions : ',img.shape)
     
    scale_percent = 60 # percent of original size
    width = int(img.shape[1] * scale_percent / 100)
    height = int(img.shape[0] * scale_percent / 100)
    dim = (width, height)
    # resize image
    resized = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)
     
    print('Resized Dimensions : ',resized.shape)
     
    cv2.imshow("Resized image", resized)
    print(filename.split('.')[0])
    # cv2.imwrite(filename.split('.')[0] + "_scaled.png", resized)
    # print(filename.split('.')[0] + '_scaled.png')
 
scale('ssssss.png')
