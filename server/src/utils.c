#include "utils.h"

int iniciar_servidor(void)
{
	int socket_servidor = crearSocketEscucha(PUERTO, logger);

	log_info(logger, "Listo para escuchar a mi cliente");

	return socket_servidor;
}

int aceptarCliente(int fd_socket)
{
	struct sockaddr_in unCliente;
	memset(&unCliente, 0, sizeof(unCliente));
	unsigned int addres_size = sizeof(unCliente);

	int fd_Cliente = accept(fd_socket, (struct sockaddr *)&unCliente, &addres_size);
	if (fd_Cliente == ERROR)
	{
		log_error(logger, "El servidor no pudo aceptar la conexión entrante \n");
	}
	else
	{
		log_info(logger, "Se conectó un proceso \n");
	}

	return fd_Cliente;
}

int esperar_cliente(int socket_servidor)
{

	int socket_cliente = aceptarCliente(socket_servidor);

	log_info(logger, "Se conecto un cliente!");

	return socket_cliente;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if (recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) != 0)
		return cod_op;
	else{
		close(socket_cliente);
		return -1;
	}
}

void *recibir_buffer(int *size, int socket_cliente)
{
	void *buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char *buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

t_list *recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void *buffer;
	t_list *valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);

	while (desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento += sizeof(int);
		char *valor = malloc(tamanio);
		memcpy(valor, buffer + desplazamiento, tamanio);
		desplazamiento += tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}