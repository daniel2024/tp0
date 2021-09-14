
SOCKETS = ../../Sockets/sockets.c

all:Cliente

Cliente: client.c  ${SOCKETS}
##importacion  de las commons 
		gcc -g client.c utils.c  ${SOCKETS} -o client -Wall -lcommons -lpthread -lreadline

clean: 
		rm -f  client *.o 