En este caso, deberemos crear un programa con el cual realizaremos el siguiente cauce Linux: ` ls -l | tail -N`.
N será un número entero que le pasaremos como entrada al programa. 
Como sabemos, el comando ls -l lista los ficheros/directorios y sus permisos del directorio actual, por otra parte, tail -N, muestra las últimas N líneas de una entrada.

A este enunciado le corresponde el programa `ejercicio1_v1.c`.

+ Ejemplo de ejecución y salida:
```
vela@Vela-PC:~/Universidad/SO/ejercicios_cauces/1$ ./ejercicio1_v1 3
Se van a intentar listar los <3> últimos ficheros del directorio: 
-rw-rw-r-- 1 vela vela  4909 nov 22 16:20 ejercicio1_v2.c
-rwxrwxr-x 1 vela vela 16072 nov 25 18:51 prueba
-rw-rw-r-- 1 vela vela  2138 nov 25 18:51 prueba.c
```

Como ejercicio adicional, implementaremos el mismo programa, pero solo mostrando los permisos.

+ Ejemplo de ejecución y salida:
```
vela@Vela-PC:~/Universidad/SO/ejercicios_cauces/1$ ./adicional 3
-rw-rw-r--
-rwxrwxr-x
-rw-rw-r--
```

Para este último programa adicional, hay dos versiones. `adicional_v1.c` y `adicional_v2.c`.

La primera versión está implementada con dos procesos hijos, el hijo 1 ejecuta el `ls -l` y escribe el resultado en el cauce 1, el hijo 2 lee el resultado del cauce 1, ejecuta el `tail -N` y lo escribe en el cauce 2.
El padre lee el resultado de dicho cauce 2 y se queda únicamente con los permisos.

La segunda versión está implementada con 3 hijos y 3 cauces.
En este caso, el hijo 3 leerá del cauce 2 el resultado de `ls -l | tail -N`, ejecutará un `cut -b 1-10` (para quedarnos con los 10 primeros bytes que son los permisos), el resultado lo escribirá en el cauce 3 y el padre simplemente leerá de este cauce.
En definitiva, este programa hará lo siguiente `ls -l | tail -3 | cut -b 1-10`.

He implmentado también una función llamada `total_ficheros` que contará el número de ficheros que hay en el directorio actual. En caso de pasarle como parámetro al programa un N más grande que el número de ficheros totales, truncaremos N a dicho número.