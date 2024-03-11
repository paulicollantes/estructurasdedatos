## Algoritmos de Ordenamiento

Este programa permite comparar la velocidad de ordenamiento de varios algoritmos implementados usando el lenguaje de programación C. Los algoritmos implementados son:

* Insertion Sort
* Selection Sort
* Merge Sort
* Quick Sort
* Heap Sort
* Counting Sort
* Radix Sort

En particular, al ejecutar el programa se permite seleccionar uno o varios algoritmos para que estos ordenen conjuntos de 1.000, 10.000 y 100.000 datos. Además, realiza ordenamiento de conjuntos de datos en orden aleateorio, ordenados y en orden inverso. El resultado se expone en tablas de datos.

### Requisitos
Los únicos requisitos son:
* Compilador C compatible (por ejemplo, GCC)
* Sistema operativo compatible con GCC (Linux, macOS, Windows con WSL, etc)


### Compilación
Para compilar el programa, se debe ejecutar el siguiente comando en la terminal:

```make```

Esto generará un archivo ejecutable llamado sort.

### Ejecución

Luego de compilar el programa, se debe ejecutar escribiendo en la consola:

```./sort```


Por supuesto, aquí está la sección agregada al README:

### Limpieza

 En caso de querer eliminar los archivos generados durante el proceso de compilación, se debe ejecutar el siguiente comando en la terminal:

```make clean```

Luego de hacer esto para volver a ejecutar se debe compilar nuevamente utilizando make.

### Data

Los archivos utilizados para la ejecución del programa son los siguientes: 

* valores_1k.txt: Conjunto de datos de 1.000 elementos en orden aleatorio.
* valores_10k.txt: Conjunto de datos de 10.000 elementos en orden aleatorio.
* valores_100k.txt: Conjunto de datos de 100.000 elementos en orden aleatorio.


* valores_1k_o.txt: Conjunto de datos de 1.000 elementos ordenados.
* valores_10k_o.txt: Conjunto de datos de 10.000 elementos ordenados.
* valores_100k_o.txt: Conjunto de datos de 100.000 elementos ordenados.


* valores_1k_r.txt: Conjunto de datos de 1.000 elementos en orden inverso.
* valores_10k_r.txt: Conjunto de datos de 10.000 elementos en orden inverso.
* valores_100k_r.txt: Conjunto de datos de 100.000 elementos en orden inverso.


