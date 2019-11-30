/*
    Sergio Vela Pelegrina. Ejercicio 1, versión 2.

    Mostrar sólo los permisos (quizás tengas que 
    crear más procesos hijos) de esos N ficheros.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#define EJECUCION_ERROR "Error al ejecutar el programa. Debe introducir un parámetro\n"
#define EJECUCION_BIEN "./ejercicio1_v2 <número entero>\n"
#define FORK_ERROR "Error en el fork"
#define PIPE_ERROR "Error en el pipe"
#define EXEC_ERROR "Error en el exec"
#define OPENDIR_ERROR "Error en el opendir"
#define CHILD_FAIL "Alguno de los hijos no se pudo ejecutar, se aborta la ejecución\n"
#define MAS_FICHEROS "Has metido más ficheros de los que hay en el directorio...\n"
#define TRUNCAR "Te lo trunco a <%d> que es el número total ;)\n"
#define os_free(x) if (x) { free(x); x = NULL; }

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

int main(int argc, char ** argv) {
    int n_ficheros;
    int contador_ficheros = 0;

    if (argc >= 2) {
        n_ficheros = atoi(argv[1]);
    } else {
        printf(EJECUCION_ERROR);
        printf(EJECUCION_BIEN);
        exit(EXIT_FAILURE);
    }

    contador_ficheros = total_ficheros();
    if (n_ficheros > contador_ficheros) {
        printf(MAS_FICHEROS);
        printf(TRUNCAR, contador_ficheros);
        n_ficheros = contador_ficheros;
    }

    int cauce1[2];
    int cauce2[2];
    pid_t hijo1;
    pid_t hijo2;
    char *comando = malloc(sizeof(char *));
    int status_child_1;
    int status_child_2;

    sprintf(comando, "%s%d", "-", n_ficheros);

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

    if ((pipe(cauce2)) < 0) {
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

        if ((execlp("tail", "tail", comando, NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    close(cauce1[0]);
    close(cauce1[1]);
    close(cauce2[1]);
    dup2(cauce2[0], STDIN_FILENO);


    char leer[1];
    char *imprimir = malloc(sizeof(char *));
    // Inicializamos el string
    memset(imprimir, 0, sizeof(char *));

    while ((read(STDIN_FILENO, leer, sizeof(leer))) != 0) {
        if (!strcmp(leer, "\n")) {
            write(STDOUT_FILENO, imprimir, 10);
            write(STDOUT_FILENO, "\n", 1);
            memset(imprimir, 0, sizeof(char *));
        } else {
            sprintf(imprimir, "%s%s", imprimir, leer);
        }
    }

    /*
        No queremos hijos en estado zombie.
    */
    hijo1 = wait(&status_child_1);
    hijo2 = wait(&status_child_2);

    os_free(comando);
    os_free(imprimir);

    return EXIT_SUCCESS;
}