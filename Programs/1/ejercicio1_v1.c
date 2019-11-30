/*
    Sergio Vela Pelegrina. Ejercicio 1, versión 1.

    Crea un programa en C de tal forma que realice el siguiente
    cauce linux: ls -l | tail -N, donde N será un número entero 
    que se le pasa como entrada a dicho programa. 
    El comando ls -l lista los ficheros/directorios y sus permisos 
    del directorio actual; y tail -N muestra las últimas N líneas 
    de una entrada. Como sabéis, el carácter barra vertical «|» realiza 
    un pipe (cauce).
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
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
    int n_ficheros;                                 /* Número pasado como argumento */
    int cauce[2];                               /* Cauce */
    pid_t hijo;                                 /* Será el identificador del hijo */
    char *comando = malloc(sizeof(char *));     /* Concatenar parámetro "-N" */


    if (argc >= 2) {
        n_ficheros = atoi(argv[1]);
    } else {
        printf("Le debes pasar un parámetro al programa.\n");
        printf("./ejercicio1 <numero_entero>.\n");
        exit(EXIT_FAILURE);
    }

    int contador_ficheros;

    contador_ficheros = total_ficheros();
    if (n_ficheros > contador_ficheros) {
        printf("Has metido más ficheros de los que hay en el directorio...\n");
        printf("Te lo trunco a <%d> que es el número total ;)\n", contador_ficheros);
        n_ficheros = contador_ficheros;
    }

    printf("Se van a intentar listar los <%d> últimos ficheros del directorio: \n", n_ficheros);

    // Creamos cauce.
    if (pipe(cauce) < 0) {
        perror(PIPE_ERROR);
        exit(EXIT_FAILURE);
    }

    // Creamos hijo.
    if ((hijo = fork()) < 0) {
        perror(FORK_ERROR);
        exit(EXIT_FAILURE);
    }

    if (hijo == 0) {                    /* Es el hijo */
        close(cauce[0]);                /* Cerramos cauce de lectura */
        dup2(cauce[1], STDOUT_FILENO);     /* Redirigimos a la salida estándar */

        // Ejecutamos el comando.
        if ((execlp("ls", "ls", "-l", NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    // Este punto únicamente lo ejecuta el padre.
    close(cauce[1]);                    /* Cerramos cauce de escritura */
    dup2(cauce[0], STDIN_FILENO);       /* Redirigimos a la entrada estándar */

    sprintf(comando, "%s%d", "-", atoi(argv[1]));
    
    if ((execlp("tail", "tail", comando, NULL)) < 0) {
        perror(EXEC_ERROR);
        exit(EXIT_FAILURE);
    }
}
