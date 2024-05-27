import cv2
import urllib.request
import numpy as np
from PIL import Image
 
def nothing(x):
    pass
 
#change the IP address below according to the
#IP shown in the Serial monitor of Arduino code
url='http://192.168.0.156/cam-lo.jpg'
 
#cv2.namedWindow(grouping)
cv2.namedWindow("live transmission", cv2.WINDOW_AUTOSIZE)
 
cv2.namedWindow("Tracking")
cv2.createTrackbar("LH", "Tracking", 0, 255, nothing) # value 0 indicates the startup value
cv2.createTrackbar("LS", "Tracking", 0, 255, nothing) # Maximum value is 255
cv2.createTrackbar("LV", "Tracking", 0, 255, nothing)
cv2.createTrackbar("UH", "Tracking", 255, 255, nothing) # starting value is 255
cv2.createTrackbar("US", "Tracking", 255, 255, nothing) # maximum value is 255
cv2.createTrackbar("UV", "Tracking", 255, 255, nothing)

# lo-res = (320,240)
# mid-res = (350,530)
# Hi-res = (800,600)

while True:
    img_resp=urllib.request.urlopen(url)
    imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
    frame=cv2.imdecode(imgnp,-1)    
    print(imgnp[255])

    #cv2.cvtColor returns an image, cv2.cvtColor(src-image color space to be changed, space conversion code, image size and depth as src image (opt), dstCn (channel number,0))   
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) #hue saturation value (HSV) / Hue saturation Brightness (HSB)
    
    #cv2.getTrackbarPos("","")
    l_h = cv2.getTrackbarPos("LH", "Tracking")
    l_s = cv2.getTrackbarPos("LS", "Tracking")
    l_v = cv2.getTrackbarPos("LV", "Tracking")
 
    u_h = cv2.getTrackbarPos("UH", "Tracking")
    u_s = cv2.getTrackbarPos("US", "Tracking")
    u_v = cv2.getTrackbarPos("UV", "Tracking")
 
    l_b = np.array([l_h, l_s, l_v])
    u_b = np.array([u_h, u_s, u_v])
    
    mask = cv2.inRange(hsv, l_b, u_b) 
    res = cv2.bitwise_and(frame, frame, mask=mask)

    mask_ = Image.fromarray(mask)

    bbox = mask_.getbbox()

    if bbox is not None:
        x1, y1, x2, y2 = bbox

        frame = cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 5)
        coordinates= [(x1, y1), (x2, y2)]
        print(l_b)
    
    img1 = cv2.resize(frame,(0,0),None,0.5,0.5)
    img2 = cv2.resize(res,(0,0),None,0.5,0.5)
    img3 = cv2.resize(mask,(0,0),None,0.5,0.5)

    img_staging = np.hstack((img1, img2, img3))

    cv2.imshow("live transmission", img_staging)
    # cv2.imshow("mask", mask)
    # cv2.imshow("res", res)
    key=cv2.waitKey(5)
    if key==ord('q'):
        break
    
cv2.destroyAllWindows()