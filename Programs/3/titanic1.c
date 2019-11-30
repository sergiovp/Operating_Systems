#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <fcntl.h>

#define EXEC_ERROR "Error en el exec"
#define FORK_ERROR "Error en el fork"
#define PIPE_ERROR "Error en el pipe"
#define OPEN_ERROR "Error en el open"

int main() {
    pid_t hijo1;
    int cauce1[2];
    char leer[1];
    int fichero;

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

        if ((execlp("cut", "cut", "-d", ";", "-f", "6", "titanic.csv", NULL)) < 0) {
            perror(EXEC_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    close(cauce1[1]);
    dup2(cauce1[0], STDIN_FILENO);
    int total_personas = 0;
    float edad_media;
    int edad_menor = 100;
    int edad_mayor = 0;
    int menores_5 = 0;
    int edades_totales = 0;
    char *edad = malloc(sizeof(char *));
    int edad_entero;

    while ((read(STDIN_FILENO, leer, sizeof(leer))) > 0) {
        char *digito = malloc(sizeof(char *));
        if (!strcmp(leer, "\n")) {
            total_personas++;
            edad_entero = atoi(edad);

            if (edad_mayor < edad_entero) {
                edad_mayor = edad_entero;
            }

            if (edad_menor > edad_entero) {
                edad_menor = edad_entero;
            }

            if (edad_entero < 5) {
                menores_5++;
            }

            edades_totales += edad_entero;
            memset(edad, 0, sizeof(char *));

        } else {
            digito = leer;
            sprintf(edad, "%s%s", edad, digito);
        }
    }
    
    edad_media = edades_totales / total_personas;

    if ((fichero = open("resultado_titanic.txt", O_CREAT | O_TRUNC | O_WRONLY, 0660)) < 0) {
        perror(OPEN_ERROR);
        exit(EXIT_FAILURE);
    }

    char personas[100];
    sprintf(personas, "%s%i\n", "Total personas: ", total_personas);
    char media[100];
    sprintf(media, "%s%f\n", "Edad media: ", edad_media);
    char joven[100];
    sprintf(joven, "%s%d\n", "La edad del más joven: ", edad_menor);
    char viejo[124];
    sprintf(viejo, "%s%d\n", "La edad del más mayor: ", edad_mayor);
    char menores[100];
    sprintf(menores, "%s%d\n", "Menores de 5 años: ", menores_5);

    write(fichero, personas, strlen(personas));
    write(fichero, media, strlen(media));
    write(fichero, joven, strlen(joven));
    write(fichero, viejo, strlen(viejo));
    write(fichero, menores, strlen(menores));

    close(fichero);
    free(edad);

    return EXIT_SUCCESS;

    /*printf("El número total de personas a bordo es de: <%i>\n", total_personas);
    printf("La edad media es de <%f> años\n", edad_media);
    printf("La edad del más joves es <%d> años\n", edad_menor);
    printf("La edad del más viejo es de <%d> años\n", edad_mayor);
    printf("El número de menores de 5 años es de <%d>\n", menores_5);*/
}