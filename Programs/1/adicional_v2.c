/*
    Sergio Vela Pelegrina. Ejercicio 1, versión 2.

    Mostrar sólo los permisos (quizás tengas que 
    crear más procesos hijos) de esos N ficheros.

    Para quedarnos únicamente con los permisos podríamos
    utilizar el comando "cut" como sigue:
    cut -b 1-10
    De forma que nos quedaremos únicamente desde el
    byte 1 hasta el 10, que son los bytes de los permisos.
    
    En este caso tendríamos lo siguiente:

    ls -l | tail -1 | cut -b 1-10

    Por consiguiente, necesitamos 3 procesos hijo y 3 cauces.

    El hijo 1 escribe el primer comando en el cauce 1, que es 
    leído por el hijo2, que a su vez escribe en el cauce 2 el
    comando 2, que es leído por el hijo 3 que escribe en el cauce 3
    el comando 3 que finalmente es leído todo por el padre desde
    el cauce 3.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#define EXEC_ERROR "Error en el exec"
#define FORK_ERROR "Error en el fork"
#define PIPE_ERROR "Error en el pipe"
#define OPENDIR_ERROR "Error en el opendir"

/*
    Función para contar el número total de 
    ficheros que hay en el directorio atual.
    En caso de que se le pase al programa como
    argumento, un número mayor de ficheros de los
    que hay, se truncará al número total de ficheros.
*/
int total_ficheros() {
    DIR *dir;
    struct dirent *dirent;
    int contador_ficheros = 0;

    if ((dir = opendir(".")) < 0) {
        perror(OPENDIR_ERROR);
        exit(EXIT_FAILURE);
    }

    while ((dirent = readdir(dir)), dirent) {
        if (!(strcmp(dirent->d_name, "..")) || !(strcmp(dirent->d_name, "."))) {
            continue;
        }
        contador_ficheros++;
    }
    closedir(dir);

    return contador_ficheros;
}

int main(int argc, char **argv) {
    int n_ficheros;
    
    if (argc >= 2) {
        n_ficheros = atoi(argv[1]);
    } else {
        printf("El programa se debe ejecutar como sigue:\n");
        printf("./ejercicio1_v2 <número de ficheros>\n");
        exit(EXIT_FAILURE);
    }

    int cauce1[2];
    int cauce2[2];
    int cauce3[2];
    pid_t hijo1;
    pid_t hijo2;
    pid_t hijo3;
    int estado_1;
    int estado_2;
    int estado_3;
    struct stat atributos;
    char *comando = malloc(sizeof(char *));
    int contador_ficheros;

    
    contador_ficheros = total_ficheros();
    if (n_ficheros > contador_ficheros) {
        printf("Has metido más ficheros de los que hay en el directorio...\n");
        printf("Te lo trunco a <%d> que es el número total ;)\n", contador_ficheros);
        n_ficheros = contador_ficheros;
    }

    // Concatenamos en 'comando' -N
    sprintf(comando, "%s%d", "-", n_ficheros);

    // Cauce 1
    if ((pipe(cauce1)) < 0) {
        perror(PIPE_ERROR);
        exit(EXIT_FAILURE);
    }

    // Hijo 1
    if ((hijo1 = fork()) < 0) {
        perror(FORK_ERROR);
        exit(EXIT_FAILURE);
    }

    // Lo ejecuta el Hijo 1
    if (hijo1 == 0) {
        close(cauce1[0]);
        dup2(cauce1[1], STDOUT_FILENO);

        if ((execlp("ls", "ls", "-l", NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    // Lo ejecuta el padre

    // Cauce 2
    if ((pipe(cauce2)) < 0) {
        perror(PIPE_ERROR);
        exit(EXIT_FAILURE);
    }

    //Hijo 2
    if ((hijo2 = fork()) < 0) {
        perror(FORK_ERROR);
        exit(EXIT_FAILURE);
    }

    // Lo ejecuta el hijo 2
    if (hijo2 == 0) {
        close(cauce1[1]);
        dup2(cauce1[0], STDIN_FILENO);

        close(cauce2[0]);
        dup2(cauce2[1], STDOUT_FILENO);

        if ((execlp("tail", "tail", comando, NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    // Lo ejecuta el padre

    // Cauce 3
    if ((pipe(cauce3)) < 0) {
        perror(PIPE_ERROR);
        exit(EXIT_FAILURE);
    }

    // Hijo 3
    if ((hijo3 = fork()) < 0) {
        perror(FORK_ERROR);
        exit(EXIT_FAILURE);
    }

    // Lo ejecuta el hijo 3
    if (hijo3 == 0) {
        close(cauce1[0]);
        close(cauce1[1]);
        close(cauce2[1]);

        dup2(cauce2[0], STDIN_FILENO);
        
        close(cauce3[0]);
        dup2(cauce3[1], STDOUT_FILENO);

        if ((execlp("cut", "cut", "-b", "1-10", NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    // Lo ejecuta el padre
    
    char leer[1];
    close(cauce1[0]);
    close(cauce1[1]);
    close(cauce2[1]);
    close(cauce2[0]);
    close(cauce3[1]);
    dup2(cauce3[0], STDIN_FILENO);

    while ((read(STDIN_FILENO, leer, sizeof(leer))) != 0) {
        printf("%s", leer);
    }
    
    /* No queremos procesos en estado zombie */
    hijo1 = wait(&estado_1);
    hijo2 = wait(&estado_2);
    hijo3 = wait(&estado_3);

    return EXIT_SUCCESS;    
}