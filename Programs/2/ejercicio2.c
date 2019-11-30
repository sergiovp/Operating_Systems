/*
    Sergio Vela Pelegrina. Ejercicio 2.

    Crea un programa en C de tal forma que 
    realice el siguiente cauce linux: 
    ls -l | wc -l

    Y además, como ese cauce escribirá en consola 
    el número de líneas, decir si ese número es par o impar.

    En este caso, debemos controlar si el número es par o impar,
    por este motivo, necesitamos dos hijos y dos cauces y que 
    el padre de éstos se dedique a controlar esto.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EXEC_ERROR "Error en el exec"
#define FORK_ERROR "Error en el fork"
#define PIPE_ERROR "Error en el pipe"
#define DUP_ERROR "Error en el dup"

/*
    Función que comprueba si el número total
    de líneas es par o impar.
*/
int es_par(int n_lineas) {
    return (n_lineas % 2 == 0 ? 1 : 0);
}

int main() {
    pid_t hijo1, hijo2;
    int cauce1[2];
    int cauce2[2];
    int status1, status2;
    char *leer = malloc(sizeof(char *));
    int n_lineas;

    if ((pipe(cauce1)) < 0) {
        perror(PIPE_ERROR);
        exit(EXIT_FAILURE);
    }

    if ((hijo1 = fork()) < 0) {
        perror(FORK_ERROR);
        exit(EXIT_FAILURE);
    }

    if (hijo1 == 0) {

        close(cauce1[0]);
        dup2(cauce1[1], STDOUT_FILENO);
        
        if ((execlp("ls", "ls", "-l", NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    
    if (pipe(cauce2) < 0) {
        perror(PIPE_ERROR);
        exit(EXIT_FAILURE);
    }

    if ((hijo2 = fork()) < 0) {
        perror(FORK_ERROR);
        exit(EXIT_FAILURE);
    }

    if (hijo2 == 0) {

        close(cauce1[1]);
        dup2(cauce1[0], STDIN_FILENO);

        close(cauce2[0]);
        dup2(cauce2[1], STDOUT_FILENO);

        if ((execlp("wc", "wc", "-l", NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    close(cauce1[0]);
    close(cauce1[1]);
    close(cauce2[1]);
    dup2(cauce2[0], STDIN_FILENO);
    read(STDIN_FILENO, leer, sizeof(char *));

    n_lineas = atoi(leer);
    
    printf("El número total de líneas es <%d>\n", n_lineas);

    if (es_par(n_lineas)) {
        printf("Es un número par de líneas\n");
    } else {
        printf("Es un número impar de líneas\n");
    }

    // No queremos procesos en estado zombie
    hijo1 = wait(&status1);
    hijo2 = wait(&status2);

    return EXIT_SUCCESS;
}