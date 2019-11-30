#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PIPE_ERROR "Error en el pipe"
#define EXEC_ERROR "Error en el exec"
#define FORK_ERROR "Error en el fork"
#define OPEN_ERROR "Error en el open"
#define WRITE_ERROR "Error en el write"
#define PERMISOS 0664

int main(int argc, char **argv) {
	
	if (argc >= 2) {
	
	} else {
		printf("Al programa se le debe pasar al menos la ruta de un archivo\n");
		printf("./bloques1 <ruta_1> ... <ruta_n>\n");
		exit(EXIT_FAILURE); 
	}
	
	char *ruta = malloc(sizeof(char *));
	int cauce[2];
	pid_t hijo;
	int estado;
	
	if ((pipe(cauce)) < 0) {
		perror(PIPE_ERROR);
		exit(EXIT_FAILURE);
	}
	
	
	for (int i = 1; i < argc; i++) {
		ruta = argv[i];
		
		if ((hijo = fork()) < 0) {
			perror(FORK_ERROR);
			exit(EXIT_FAILURE);
		}
		
		if (hijo == 0) {
			close(cauce[0]);
			dup2(cauce[1], STDOUT_FILENO);
			
			if ((execlp("du", "du", "-k", argv[i], NULL)) < 0) {
				perror(EXEC_ERROR);
				exit(EXIT_FAILURE);
			}
		}
	}
	
	close(cauce[1]);
	dup2(cauce[0], STDIN_FILENO);
	
	char leer[1];
	int cont = 1;
	char *contenido = malloc(sizeof(char *));
	memset(contenido, 0, sizeof(char *));
	int fichero;
	char *nombre_fichero = malloc(sizeof(char *));

	while((read(STDIN_FILENO, leer, sizeof(leer))) != 0) {
		if (!strcmp(leer, "\n")) {
			sprintf(nombre_fichero, "%s%s%i%s", "/tmp/", "dato_", cont, ".txt");
			
			if ((fichero = open(nombre_fichero, O_CREAT | O_TRUNC | O_WRONLY, PERMISOS)) < 0) {
				perror(OPEN_ERROR);
				exit(EXIT_FAILURE);
			}
			
			sprintf(contenido, "%s%s", contenido, "\n");
			
			if ((write(fichero, contenido, strlen(contenido))) < 0) {
				perror(WRITE_ERROR);
				exit(EXIT_FAILURE);
			}
			close(fichero);
			
			cont++;
			memset(contenido, 0, sizeof(char *));
		} else {
			sprintf(contenido, "%s%s", contenido, leer);
		}
	}
	
	// No queremos procesos en estado zombie. A parte, informamos del estado de terminación del hijo
	while ((hijo = wait(&estado)) > 0) {
		printf("El hijo <%d> ha terminado con estado <%d>\n", hijo, estado);
	}
}
