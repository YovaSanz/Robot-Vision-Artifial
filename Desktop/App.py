from tkinter import *
import socket

ESP_IP = '192.168.137.190' #IP de nuestro modulo

ESP_PORT = 8266 #puerto que hemos configurado para que abra ESP

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #Creamos el onjeto socket

def key_pressed(c):
    print(c.char)
    print(c.char.encode(encoding='utf_8'))
    s.send(c.char.encode(encoding='utf_8'))

root = Tk() #Creamos el contenedor denuestros objetos
root.title("Controlador ESP38") #Cambianos el titulo a nuestra ventana

frame = Frame (root) #creamos el contenedor de nuestros objetos

lbl_titulo = Label(frame, text='Controlador Robot ESP32') #creamos testo para la ventana
lbl_titulo.grid(row=0, column=0, pady=20, padx=20) #añadimos el tirulo a nuestra app

frame.bind("<KeyPress>", key_pressed)

s.connect((ESP_IP , ESP_PORT)) #nos conectamos a la IP y el puesto que hemos decignado

frame.pack()
frame.focus_set()

root.mainloop()
