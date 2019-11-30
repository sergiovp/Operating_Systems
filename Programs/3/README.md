En este caso, crearemos un programa llamado `titanic1.c` que ejecutará la siguiente orden `cut -d";" -f 6 titanic.csv`.
Con este comando nos quedaremos únicamente con las edades de los pasajeros del titanic, especificadas en el fichero `titanic.csv` que también se proporciona.

Debemos quedarnos con un listado de los siguientes datos:

+ Total de personas a bordo
+ Edad media de los pasajeros
+ Edad del más jovem
+ Edad del más viejo
+ Número total de pasajeros menores de 5 años

Dicha información no la imprimiremos por la salida estándar, sino que la guardaremos en un fichero de nombre `resultado_titanic.txt` que se creará en el directorio de trabajo.

+ Ejemplo de ejecución y salida:
~~~
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenTitanic$ ls
titanic1  titanic1.c  titanic.csv
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenTitanic$ ./titanic1 
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenTitanic$ ls
resultado_titanic.txt  titanic1  titanic1.c  titanic.csv
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenTitanic$ cat resultado_titanic.txt 
Total personas: 714
Edad media: 29.000000
La edad del más joven: 0
La edad del más mayor: 80
Menores de 5 años: 40
~~~