import cv2
import numpy as np

def nothing(x):
    pass


cv2.namedWindow('Trackbars')


cv2.createTrackbar('L Min', 'Trackbars', 0, 255, nothing)
cv2.createTrackbar('A Min', 'Trackbars', 0, 255, nothing)
cv2.createTrackbar('B Min', 'Trackbars', 0, 255, nothing)
cv2.createTrackbar('L Max', 'Trackbars', 255, 255, nothing)
cv2.createTrackbar('A Max', 'Trackbars', 255, 255, nothing)
cv2.createTrackbar('B Max', 'Trackbars', 255, 255, nothing)

cap = cv2.VideoCapture(0)  

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.resize(frame, (320, 240))

    lab = cv2.cvtColor(frame, cv2.COLOR_BGR2LAB)

    l_min = cv2.getTrackbarPos('L Min', 'Trackbars')
    a_min = cv2.getTrackbarPos('A Min', 'Trackbars')
    b_min = cv2.getTrackbarPos('B Min', 'Trackbars')
    l_max = cv2.getTrackbarPos('L Max', 'Trackbars')
    a_max = cv2.getTrackbarPos('A Max', 'Trackbars')
    b_max = cv2.getTrackbarPos('B Max', 'Trackbars')


    lower = np.array([l_min, a_min, b_min])
    upper = np.array([l_max, a_max, b_max])
    mask = cv2.inRange(lab, lower, upper)


    cv2.imshow('Frame', frame)
    cv2.imshow('Mask', mask)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

