## Búsqueda e Inserción

Este programa permite medir y comparar el tiempo de ejecución de operaciones de búsqueda e inserción en diferentes estructuras de datos implementadas usando el lenguaje de programación C. Las estructuras de datos evaluadas son:

* Árbol Binario de Búsqueda (BST)
* Árbol AVL
* Tabla Hash

### Requisitos
Los únicos requisitos son:
* Compilador C compatible (por ejemplo, GCC)
* Sistema operativo compatible con GCC (Linux, macOS, Windows con WSL, etc)

### Compilación
Para compilar el programa, se debe ejecutar el siguiente comando en la terminal:

```make```

Esto generará un archivo ejecutable llamado search.

### Ejecución
Una vez compilado, se puede ejecutar el programa escribiendo en la consola:

```./tree```

### Limpieza
En caso de querer eliminar los archivos generados durante el proceso de compilación, se debe ejecutar el siguiente comando en la terminal:

```make clean```

Después de esto, se debe compilar nuevamente utilizando make.

### Datos

Los archivos utilizados para la ejecución del programa son los siguientes:

* datos.txt: Conjunto de 100.000 datos en orden aleatorio
* datos_o.txt: Conjunto de 100.000 datos ordenados
* datos_r.txt: Conjunto de 100.000 datos en orden inverso

