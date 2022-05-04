import pygame
import json
import httplib2

http = httplib2.Http()
pygame.init()

aberta = True

def sendData(key):
    url_json = 'http://192.168.0.102/controller'   
    data = {'command': key}
    headers={'Content-Type': 'application/json; charset=UTF-8'}
    response, content = http.request(url_json, 'POST', headers=headers, body=json.dumps(data))
    return (key)

def main():
    global aberta
    clock = pygame.time.Clock()
    running = True
 
    joysticks = [pygame.joystick.Joystick(i) for i in range(pygame.joystick.get_count())]
    for joy in joysticks:
        joy.init()
 
    while running:
        for event in pygame.event.get():
            if event.type == pygame.JOYAXISMOTION:
                if event.axis == 2:
                    value = event.value
                    if value > 0.9: #Dir
                        print("Dir",value)
                        print(sendData("5"))                        

                    if value < -0.9: #Esq
                        print("Esq",value)
                        print(sendData("6"))

                if event.axis == 3:
                    value = event.value
                    if value > 0.9: #Baixo
                        print("Baixo",value)
                        print(sendData("8"))


                    if value < -0.9: #Cima
                        print("Cima",value)
                        print(sendData("7"))

                        
            if event.type == pygame.JOYHATMOTION:
                print(event)
                frenteTras = event.value[1]
                dirEsq = event.value[0]


                if frenteTras == 1:
                    print(sendData("3"))
                if frenteTras == -1:
                    print(sendData("4"))
                

                if dirEsq == 1:
                    print(sendData("1"))
                if dirEsq == -1:
                    print(sendData("2"))

                if frenteTras == 0 and dirEsq==0:
                    print(sendData("-2"))

                #print(frenteTras)
            elif event.type == pygame.JOYBUTTONDOWN:
                button = event.button
                print("Botão: ", button)
                if(button == 11):
                    if(aberta):
                        print(sendData("9"))
                        aberta = False
                    else:
                        print(sendData("10"))
                        aberta = True
 
        #clock.tick(20)
 
    pygame.quit()
 
main()
