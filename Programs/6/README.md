Crea un programa llamado `programa1.c` que recorra el directorio actual y muestre los archivos con **todos los permisos para usuario, grupo y otros (777)** y **cuyo nombre sea mayor que 7 bytes**.

+ Ejemplo de ejecución y salida:
~~~
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenLunes$ ls -l
total 44
drwxrwxr-x 2 vela vela  4096 nov 26 20:06 FicherosCopia
-rwxrwxrwx 1 vela vela     0 nov 26 12:03 hola
-rwxrwxrwx 1 vela vela     0 nov 26 16:37 holahola
drwxrwxrwx 2 vela vela  4096 nov 30 18:57 jejejejejejeje
-rwxrwxrwx 1 vela vela     0 nov 26 16:37 lgflewkgfwl
-rwxrwxrwx 1 vela vela     0 nov 26 16:52 netflix
-rwxrwxr-x 1 vela vela  8792 nov 26 16:52 programa1
-rw-rw-r-- 1 vela vela  1101 nov 27 11:53 programa1.c
-rwxrwxr-x 1 vela vela 13144 nov 26 16:59 programa2
-rw-r--r-- 1 vela vela  1519 nov 27 11:53 programa2.c
-rwxrwxrwx 1 vela vela     0 nov 26 16:37 SergioVela
-rwxrwx--- 1 vela vela     0 nov 26 15:58 SergioVelaholahola
-rwxrwx--- 1 vela vela     0 nov 26 15:58 SergioVelaholaholalgflewkgfwl
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenLunes$ ./programa1
SergioVela
holahola
netflix
lgflewkgfwl
jejejejejejeje
~~~

Cree otro programa llamado `programa2.c` en el cual se creará un proceso hijo que ejecutará el programa anterior. El padre creará una copia de los ficheros que sean regulares leídos por el hijo en un directorio especificado. En el caso en el que se lea algún directorio, se creará igualmente un **fichero** con ese mismo nombre.
Los ficheros creados deberán tener todos los permisos para usuario y grupo y ninguno para otros (770).

+ Ejemplo ejecución y salida:
~~~
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenLunes$ ./programa2
/home/vela/Universidad/SO/examenes_clase/ExamenLunes/FicherosCopia/SergioVela
/home/vela/Universidad/SO/examenes_clase/ExamenLunes/FicherosCopia/holahola
/home/vela/Universidad/SO/examenes_clase/ExamenLunes/FicherosCopia/netflix
JAJA
/home/vela/Universidad/SO/examenes_clase/ExamenLunes/FicherosCopia/lgflewkgfwl
/home/vela/Universidad/SO/examenes_clase/ExamenLunes/FicherosCopia/jejejejejejeje
vela@Vela-PC:~/Universidad/SO/examenes_clase/ExamenLunes$ ls -l FicherosCopia/
total 0
-rwxrwx--- 1 vela vela 0 nov 30 19:02 holahola
-rwxrwx--- 1 vela vela 0 nov 30 19:02 jejejejejejeje
-rwxrwx--- 1 vela vela 0 nov 30 19:02 lgflewkgfwl
-rwxrwx--- 1 vela vela 0 nov 30 19:02 netflix
-rwxrwx--- 1 vela vela 0 nov 30 19:02 SergioVela
~~~

**Importante**: para poder ejecutar correctamente este programa en otro ordenador, deberá modificar la línea de código 52 de `programa2.c`, especificando una ruta a un directorio existente de tu ordenador.