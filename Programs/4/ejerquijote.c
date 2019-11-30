#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define PIPE_ERROR "Error en el pipe"
#define FORK_ERROR "Error en el fork"
#define EXEC_ERROR "Error en el exec"
#define OPEN_ERROR "Error en el open"
#define WRITE_ERROR "Error en el write"

int main() {
    int cauce[2];
    int cauce2[2];
    pid_t hijo;
    pid_t hijo2;
    char salida[1024];
    char *cadena = malloc(sizeof(char *));
    long int tamanio;
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

        if ((execl("./tam_quijote", "./tam_quijote", NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    close(cauce[1]);
    dup2(cauce[0], STDIN_FILENO);

    read(STDIN_FILENO, salida, sizeof(salida));
    tamanio = atoi(salida);
    
    if ((fichero = open("resultado.txt", O_CREAT | O_TRUNC | O_WRONLY, 0664)) < 0) {
        perror(OPEN_ERROR);
        exit(EXIT_FAILURE);
    }

    sprintf(cadena, "%s%li%s", "Tamaño quijote.txt: ", tamanio, "\n");

    if ((write(fichero, cadena, strlen(cadena))) < 0) {
        perror(WRITE_ERROR);
        exit(EXIT_FAILURE);
    }

    if ((pipe(cauce2)) < 0) {
        perror(PIPE_ERROR);
        exit(EXIT_FAILURE);
    }

    if ((hijo2 = fork()) < 0) {
        perror(FORK_ERROR);
        exit(EXIT_FAILURE);
    }

    if (hijo2 == 0) {
        close(cauce2[0]);
        dup2(cauce2[1], STDOUT_FILENO);

        if ((execlp("wc", "wc", "-w", "quijote/quijote.txt", NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    
    close(cauce2[1]);
    dup2(cauce2[0], STDIN_FILENO);

    read(STDIN_FILENO, salida, 6);

    sprintf(cadena, "%s%s\n", "Palabras: ", salida);
    
    write(fichero, cadena, strlen(cadena));

    close(fichero);

    return EXIT_SUCCESS;
}