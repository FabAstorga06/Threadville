import socket

ip_address = ""
port = 8888
connections = 3

#Se crea el socket para comunicacion
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Se indica al socket el puerto e ip que debe estar esperando
# ip vacio para que acepte cualquier conexion externa
s.bind((ip_address, port))
 
#Se acepta conexion entrante y se indica el numero de conexiones que puede establecer
s.listen(connections)
 
#Se instancia socket cliente para recibir datos
#Devuelve tupla con datos de conexion: IP y puerto
sc, addr = s.accept()
print("Available connection...")

#Mantiene conexion abierta 
while True: 
	
    #Recibe el mensaje y como parametro la cantidad de bytes a recibir
    msg_recv = sc.recv(1024)
 
    #Si el mensaje recibido "close", se cierra la socket y la app
    if msg_recv == "close":
        break
 
    #Si se reciben datos, este muestra la IP y el mensaje recibido
    print str(addr[0]) + " dice: ", msg_recv
 
    #Se devuelve el mensaje al cliente
    sc.send(msg_recv)
    
print "Cerrando la conexion..."
 
#Se cierra la instancia del socket cliente
sc.close()
s.close()
