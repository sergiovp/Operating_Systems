#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define PIPE_ERROR "Error en el pipe"
#define EXEC_ERROR "Error en el exec"
#define FORK_ERROR "Error en el fork"

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
	while((read(STDIN_FILENO, leer, sizeof(leer))) != 0) {
		printf("%s", leer);
	}
}
