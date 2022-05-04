import cv2
import pygame
import json
import httplib2

http = httplib2.Http()
pygame.init()

cap = cv2.VideoCapture("http://192.168.0.101:8080/video")

joysticks = [pygame.joystick.Joystick(i) for i in range(pygame.joystick.get_count())]
for joy in joysticks:
    joy.init()

while True:
    _, frame = cap.read()
    cv2.imshow("Carrinho", frame)
    cv2.waitKey(1)

    for event in pygame.event.get():
        if event.type == pygame.JOYBUTTONDOWN:
            button = event.button
            print(button)
            if(button == 0):
                response, content = http.request("http://192.168.0.101:8080/enabletorch", 'POST')
                print(response, content)
            if(button == 1):
                response, content = http.request("http://192.168.0.101:8080/disabletorch", 'POST')
                print(response, content)
            if(button == 5):
                response, content = http.request("http://192.168.0.101:8080/settings/ffc?set=off", 'POST')
                print(response, content)
            if(button == 4):
                response, content = http.request("http://192.168.0.101:8080/settings/ffc?set=on", 'POST')
                print(response, content)
        
