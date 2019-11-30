#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define OPEN_ERROR "Error en el open"
#define PIPE_ERROR "Error en el pipe"
#define FORK_ERROR "Error en el fork"
#define EXEC_ERROR "Error en el exec"
#define OPEN_ERROR "Error en el open"
#define PERMISOS 0770

int main() {
	pid_t hijo;
	int cauce[2];
	int status;
	char leer[1];
	int fichero;
	
	if ((pipe(cauce)) < 0) {
		perror(PIPE_ERROR);
		exit(EXIT_FAILURE);
	}
	
	if ((hijo = fork()) < 0) {
		perror(FORK_ERROR);
		exit(EXIT_FAILURE);
	}
	
	if (hijo == 0) {
		close(cauce[0]);
		dup2(cauce[1], STDOUT_FILENO);
		
		if ((execl("./programa1", "./programa1", NULL)) < 0) {
			perror(EXEC_ERROR);
			exit(EXIT_FAILURE);
		}
	}
	
	close(cauce[1]);
	dup2(cauce[0], STDIN_FILENO);
	
	setbuf(stdout, NULL);

	char *nombre_fichero = malloc(sizeof(char *));
	char *ruta = malloc(sizeof(char *));
	
	sprintf(ruta, "%s", "/home/vela/Universidad/SO/examenes_clase/ExamenLunes/FicherosCopia/");

	while ((read(STDIN_FILENO, leer, sizeof(leer))) != 0) {		
		
		if (!strcmp(leer, "\n")) {	
			sprintf(ruta, "%s%s", ruta, nombre_fichero);
			printf("%s\n", ruta);
			
			if ((fichero = open(ruta, O_CREAT | O_TRUNC | O_WRONLY, PERMISOS)) < 0) {
				perror(OPEN_ERROR);
				exit(EXIT_FAILURE);
			}
			memset(ruta, 0, sizeof(char *));
			memset(nombre_fichero, 0, sizeof(char *));
		}
		else {
			sprintf(nombre_fichero, "%s%s", nombre_fichero, leer);
		}
	}
}
