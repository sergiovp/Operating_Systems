#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <ftw.h>

#define S_IRWXUWOTH 0702
#define NFTW_ERROR "Error en la función nftw"
#define CHECK_CRITERIOS(modo, tam) S_ISREG(modo) && ((modo & S_IRWXUWOTH) == S_IRWXUWOTH) && tam > 7

int recorrido_directorio(const char* path, const struct stat *atributos, int type_flag, struct FTW *ftwbuf) {    
    
    char *nombre_fichero = strrchr(path, '/');
    if (nombre_fichero) {
        nombre_fichero += 1;
    }
    
    if (CHECK_CRITERIOS(atributos->st_mode, strlen(nombre_fichero))) {
        printf("%s|%o|%li\n", nombre_fichero, atributos->st_mode  & ~S_IFMT, atributos->st_size);
    }
    return EXIT_SUCCESS;
}

int main() {
    char *ruta = malloc(sizeof (char *));
    sprintf(ruta, "%s", "ficheros");

    if ((nftw(ruta, recorrido_directorio, 10, 0)) != 0) {
        perror(NFTW_ERROR);
        exit(EXIT_FAILURE);
    }
}
