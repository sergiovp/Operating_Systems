/*
    Programa que recorre el directorio actual e imprima el nombre
    de los archivos regulares con permisos 777 y nombre de longitud
    mayor a 7.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define READDIR_ERROR "Error en el readdir"
#define OPENDIR_ERROR "Error en el readdir"
#define STAT_ERROR "Error en el stat"
#define S_IRWXUGO 0777
#define CHECK_REQUISITOS(mode, longitud) ((mode & S_IRWXUGO) == S_IRWXUGO) && longitud > 7

int main() {
	DIR *dir;
	struct dirent *dirent;
	struct stat atributos;
	char *nombre = malloc(sizeof(char *));
	
	if ((dir = opendir(".")) < 0) {
		perror(OPENDIR_ERROR);
		exit(EXIT_FAILURE);
	}
	
	while ((dirent = readdir(dir)), dirent) {
		if ((stat(dirent->d_name, &atributos)) < 0) {
			perror(STAT_ERROR);
			exit(EXIT_FAILURE);
		}
	
	
		if (CHECK_REQUISITOS(atributos.st_mode, strlen(dirent->d_name))) {
			sprintf(nombre, "%s%s", dirent->d_name, "\n");
			printf("%s", nombre);
			memset(nombre, 0, sizeof(char *));
		}
	}
	
	return EXIT_SUCCESS;
}
