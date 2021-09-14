#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char *ip;
	int puerto;
	char *valor;

	t_log *logger;
	t_config *config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	ip = config_get_string_value(config, "IP_SERVER");

	puerto = config_get_int_value(config, "PUERTO");

	valor = config_get_string_value(config, "CLAVE");

	//log_info(logger, "valor clave: %s", valor);

	//Loggear valor de config

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor

	conexion = crear_conexion(ip, puerto, logger);

	//enviar CLAVE al servirdor
	enviar_mensaje(valor, conexion);
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log *iniciar_logger(void)
{
	t_log *nuevo_logger = log_create("tp0.log", "TP0_log", 1, LOG_LEVEL_INFO);
	if (nuevo_logger == NULL)
	{
		printf("Error in created logger\n");
		exit(1);
	}

	return nuevo_logger;
}

t_config *iniciar_config(void)
{
	t_config *nuevo_config = config_create("../../Config/tp0.config");
	if (nuevo_config == NULL)
	{
		printf("Error in created_config\n");
		exit(1);
	}

	return nuevo_config;
}

void leer_consola(t_log *logger)
{

	char *leido;
	while (strncmp(leido, "\0", 1))
	{
		//El primero te lo dejo de yapa
		leido = readline(">");

		log_info(logger, leido);

		// Acá la idea es que imprimas por el log lo que recibis de la consola.
	}
	free(leido);
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char *leido;
	t_paquete *paquete = crear_paquete();

	while (strncmp(leido, "\0", 1))
	{
		//El primero te lo dejo de yapa
		leido = readline(">");
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
	}
	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);
	free(leido);
}

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
