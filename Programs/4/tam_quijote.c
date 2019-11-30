#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define STAT_ERROR "Error en el stat con el fichero <%s>\n"
#define OPENDIR_ERROR "Error en el opendir"
#define RUTA_DIR "quijote/"
#define MENSAJE_PERMISOS "El fichero <%s> tiene todos los permisos para usuario, ninguno para grupo y de escritura para otros\n"

int main() {
    struct stat atributos;
    DIR *dir;
    struct dirent *dirent;
    char ruta[PATH_MAX];
    char permisos[24];

    if ((dir = opendir("quijote")) < 0) {
        perror(OPENDIR_ERROR);
        exit(EXIT_FAILURE);
    }

    while ((dirent = readdir(dir)), dirent) {
        
        sprintf(ruta, "%s%s", RUTA_DIR, dirent->d_name);

        if ((stat(ruta, &atributos)) < 0) {
            printf(STAT_ERROR, dirent->d_name);
            perror(STAT_ERROR);
            exit(EXIT_FAILURE);
        }

        if (!strcmp(dirent->d_name, "quijote.txt")) {
            printf("%li", atributos.st_size);
        }
    }
}