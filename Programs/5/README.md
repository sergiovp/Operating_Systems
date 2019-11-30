Crea un programa llamado `bloques1.c` que recibirá cierto número de argumentos. Cada uno de ellos será la ruta de un archivo. Para cada argumento recibido, se deberá crear un proceso hijo que lance la ejecución del comando `du -k argv[i]`, dicho comando escribe en la salida estándar el número de bloques (de 1024 bytes) asignados a la ruta que le pasamos (argv[i]) en nuestro caso.

Los procesos hijos se comonicarán con el padre mediante un cauce.

+ Ejemplo de ejecución y salida:
~~~
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenMiercoles$ ./bloques1 . ../
64	.
40	../Ejercicio1
64	../ExamenMiercoles
4	../ExamenLunes/FicherosCopia
44	../ExamenLunes
4	../ExamenQuijote/quijote/dfw
4	../ExamenQuijote/quijote/qwfh
1048	../ExamenQuijote/quijote
1092	../ExamenQuijote
84	../ExamenTitanic
1328	../
~~~

Se creará otro ejercicio llamado `bloques2.c` como ampliación del ejercicio anterior. En este caso, por cada dato leído por el padre del cauce, se guardará en un archivo en `/tmp` con nombre `dato_N.txt` donde N es un contandor inicializado a 1 y que va a ir incrementándose por cada lectura. Como contenido de cada fichero, tendremos el número de bloques asociado.

+ Ejemplo de ejecución y salida:
~~~
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenMiercoles$ ./bloques2 . ../
El hijo <20496> ha terminado con estado <0>
El hijo <20497> ha terminado con estado <0>
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenMiercoles$ ls -l /tmp/
total 44
-rw-rw-r-- 1 vela vela 20 nov 30 18:43 dato_10.txt
-rw-rw-r-- 1 vela vela  9 nov 30 18:43 dato_11.txt
-rw-rw-r-- 1 vela vela  5 nov 30 18:43 dato_1.txt
-rw-rw-r-- 1 vela vela 17 nov 30 18:43 dato_2.txt
-rw-rw-r-- 1 vela vela 22 nov 30 18:43 dato_3.txt
-rw-rw-r-- 1 vela vela 31 nov 30 18:43 dato_4.txt
-rw-rw-r-- 1 vela vela 18 nov 30 18:43 dato_5.txt
-rw-rw-r-- 1 vela vela 31 nov 30 18:43 dato_6.txt
-rw-rw-r-- 1 vela vela 32 nov 30 18:43 dato_7.txt
-rw-rw-r-- 1 vela vela 30 nov 30 18:43 dato_8.txt
-rw-rw-r-- 1 vela vela 22 nov 30 18:43 dato_9.txt
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenMiercoles$ cat /tmp/dato_1.txt 
64	.
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenMiercoles$ cat /tmp/dato_7.txt 
4	../ExamenQuijote/quijote/qwfh
~~~