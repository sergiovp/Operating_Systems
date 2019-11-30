Crea un programa llamado `tam_quijote.c` el cuál realizará una exploración a un solo nivel, (sin descenso), del directorio llamado `quijote`. Dicho programa mostrará por pantalla el tamaño el bytes **únicamente** del fichero `quijote.txt`.

+ Ejemplo de ejecución y salida:
~~~
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenQuijote$ ./tam_quijote 
10602590
~~~

Se deberá crear un programa adicional llamado `ejerquijote.c` el cual creará un cauce para comunicar un proceso hijo que ejecutará el programa anterior `tam_quijote.c` con el padre, el cual leerá el resultado y tendrá que escribir en un fichero que se creará en el mismo directorio llamado `resultado.txt` el tamaño del quijote y el número de palabras con el siguiente formato:
~~~
Tamaño quijote.txt: 1060259
Palabras: 1870189
~~~

+ Ejemplo de ejecución y salida:
~~~
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenQuijote$ ./ejerquijote 
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenQuijote$ cat resultado.txt 
Tamaño quijote.txt: 1060259
Palabras: 1870189
~~~