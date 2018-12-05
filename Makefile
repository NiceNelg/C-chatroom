server:socket.o server.o dlist.o
	gcc -o server socket.o server.o dlist.o
server.o:server.c socket.h
	gcc -c server.c
socket.o:socket.c socket.h
	gcc -c socket.c
dlist.o:dlist.c dlist.h
	gcc -c dlist.c
