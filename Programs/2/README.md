En este caso, crearemos un programa para ejecutar el siguiente pipe ` ls -l | wc -l`. Dicho comando nos mostrará el número de líneas.
Se podría hacer con un único proceso hijo que ejecute el `ls -l` y el padre que ejecutaría el `wc -l`.
Para hacerlo un poco más interesante, el programa también deberá mostrar si el número de líneas es par o impar, con lo cual, deberemos tener dos procesos hijo.

+ Ejemplo de ejecución y salida:
~~~
vela@Vela-PC:~/Universidad/SO/ejercicios_cauces/2$ ls -l
total 20
-rwxrwxr-x 1 vela vela 13000 nov 30 17:23 ejercicio2
-rw-rw-r-- 1 vela vela  2441 nov 22 16:46 ejercicio2.c
vela@Vela-PC:~/Universidad/SO/ejercicios_cauces/2$ ./ejercicio2 
El número total de líneas es <3>
Es un número impar de líneas
vela@Vela-PC:~/Universidad/SO/ejercicios_cauces/2$ touch hola.txt
vela@Vela-PC:~/Universidad/SO/ejercicios_cauces/2$ ls -l
total 20
-rwxrwxr-x 1 vela vela 13000 nov 30 17:23 ejercicio2
-rw-rw-r-- 1 vela vela  2441 nov 22 16:46 ejercicio2.c
-rw-rw-r-- 1 vela vela     0 nov 30 17:23 hola.txt
vela@Vela-PC:~/Universidad/SO/ejercicios_cauces/2$ ./ejercicio2 
El número total de líneas es <4>
Es un número par de líneas
~~~