# Sistemas Operativos

Repositorio dedicado al desarrollo e implementación de programas en C que hagan uso de llamadas al sistema Linux.

Las llamadas que veremos para el SA (Sistema de Archivos) serán:

+ open
+ read
+ write
+ close
+ stat
+ umask
+ chmod

Como sabemos, los directorios también se podrían leer utilizando las mismas llamadas que para archivos normales, lo cual no es una buena práctica ya que la estructura de los directorios puede cambiar de un sistema a otro, haciendo que los programas no sean transportables.
Utilizaremos por tanto una biblioteca estándar `(<sys/types.h> y <dirent.h>)` y del tipo *DIR* y la estructura *dirent* para dicho manejo de directorios. Algunas de las funciones que utilizaremos serán:

+ opendir
+ readdir
+ closedir
+ telldir
+ nftw

Para el control de procesos:

+ fork
+ wait
+ exit
+ Familia exec

Para la comunicación de procesos con pipes (cauces):

+ pipe