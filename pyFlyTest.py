import pyFly
import cv2

if not pyFly.initCamera(1):
    print('camera is not detected.')
    exit()

while(True):
    image = pyFly.getImage();
    # ---- rotate 90 degree ----
    #image = cv2.transpose(image);
    #image = cv2.flip(image,1); # clockwise
    #image = cv2.flip(image,0); # counter clockwise
    # ----

    cv2.imshow('pyFly', image)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

pyFly.closeCamera()

