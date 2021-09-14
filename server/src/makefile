
SOCKETS = ../../Sockets/sockets.c


all:Server

Server: server.c  ${SOCKETS} 
##importacion  de las commons 
		gcc -g server.c utils.c  ${SOCKETS} -o server -Wall -lcommons -lpthread 

clean: 
		rm -f  server *.o 