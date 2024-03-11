#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_SIZE 100000

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selectionSort(int array[], int size) {
  for (int step = 0; step < size - 1; step++) {
    int min_idx = step;
    for (int i = step + 1; i < size; i++) {
      if (array[i] < array[min_idx])
        min_idx = i;
    }

    swap(&array[min_idx], &array[step]);
  }
}

void insertionSort(int array[], int size) {
  for (int step = 1; step < size; step++) {
    int key = array[step];
    int j = step - 1;

    while (key < array[j] && j >= 0) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}

void merge(int arr[], int p, int q, int r) {

  int n1 = q - p + 1;
  int n2 = r - q;
  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l < r) {

    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}


int partition(int array[], int low, int high) {
  
  int pivot = array[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }

  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);

    quickSort(array, low, pi - 1);

    quickSort(array, pi + 1, high);
  }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    if (largest != i) {
      swap(&arr[i], &arr[largest]);
      heapify(arr, n, largest);
    }
  }
  
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);
  
    for (int i = n - 1; i >= 0; i--) {
      swap(&arr[0], &arr[i]);
      heapify(arr, i, 0);
    }
}

void countingSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int *count = (int *)malloc((max + 1) * sizeof(int));
    if (count == NULL) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[index] = i;
            index++;
            count[i]--;
        }
    }

    free(count);
}



int getMax(int array[], int n) {
  int max = array[0];
  for (int i = 1; i < n; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}


void countingSortR(int arr[], int n, int exp) {
    const int range = 10;  
    int *count = (int *)malloc(range * sizeof(int));
    if (count == NULL) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < range; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    int *output = (int *)malloc(n * sizeof(int));
    if (output == NULL) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

void radixSort(int array[], int size) {
  int max = getMax(array, size);

  for (int place = 1; max / place > 0; place *= 10)
    countingSortR(array, size, place);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void medirTiempoA(void (*algoritmo)(int[], int), int array0[], int array1[], int array2[], int n0, int n1, int n2, const char *nombreAlgoritmo) {
    
    clock_t start_time_0 = clock();
    algoritmo(array0, n0);
    clock_t end_time_0 = clock();
    double elapsed_time_0 = ((double)(end_time_0 - start_time_0)) / CLOCKS_PER_SEC;

    clock_t start_time_1 = clock();
    algoritmo(array1, n1);
    clock_t end_time_1 = clock();
    double elapsed_time_1 = ((double)(end_time_1 - start_time_1)) / CLOCKS_PER_SEC;

    clock_t start_time_2 = clock();
    algoritmo(array2, n2);
    clock_t end_time_2 = clock();
    double elapsed_time_2 = ((double)(end_time_2 - start_time_2)) / CLOCKS_PER_SEC;

    printf("%-15s\t | %f  |  %f  |  %f  |\n", nombreAlgoritmo, elapsed_time_0, elapsed_time_1, elapsed_time_2);

}

void medirTiempoB(void (*algoritmo)(int[], int, int), int array0[], int array1[], int array2[], int s, int n0, int n1, int n2, const char *nombreAlgoritmo) {
    
    clock_t start_time_0 = clock();
    algoritmo(array0, s, n0);
    clock_t end_time_0 = clock();
    double elapsed_time_0 = ((double)(end_time_0 - start_time_0)) / CLOCKS_PER_SEC;

    clock_t start_time_1 = clock();
    algoritmo(array1, s, n1);
    clock_t end_time_1 = clock();
    double elapsed_time_1 = ((double)(end_time_1 - start_time_1)) / CLOCKS_PER_SEC;

    clock_t start_time_2 = clock();
    algoritmo(array2, s, n2);
    clock_t end_time_2 = clock();
    double elapsed_time_2 = ((double)(end_time_2 - start_time_2)) / CLOCKS_PER_SEC;

    printf("%-15s\t | %f  |  %f  |  %f  |\n", nombreAlgoritmo, elapsed_time_0, elapsed_time_1, elapsed_time_2);

}

int main() {
    int arr0[1000];
    int arr1[10000];
    int arr2[100000];


    int opciones;
    int opciones_ingresadas[10];  // Se asume que el usuario ingresa hasta 10 opciones

    
    printf("Algoritmos: ");
    printf("1. Insertion Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Merge Sort\n");
    printf("4. Quick Sort\n");
    printf("5. Heap Sort\n");
    printf("6. Counting Sort\n");
    printf("7. Radix Sort\n");
    printf("Ingrese una serie de opciones (por ejemplo, 134): ");
    scanf("%d", &opciones);

    int num_opciones = 0;

    while (opciones != 0 && num_opciones < 10) {
        opciones_ingresadas[num_opciones] = opciones % 10;
        opciones /= 10;
        num_opciones++;
    }

    FILE *file = fopen("data/valores_1k.txt", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    int n0 = 0;
    while (fscanf(file, "%d", &arr0[n0]) == 1) {
        n0++;
    }

    fclose(file);

    FILE *file1 = fopen("data/valores_10k.txt", "r");
    if (file1 == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    int n1 = 0;
    while (fscanf(file1, "%d", &arr1[n1]) == 1) {
        n1++;
    }

    fclose(file1);

    FILE *file2 = fopen("data/valores_100k.txt", "r");
    if (file2 == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    int n2 = 0;
    while (fscanf(file2, "%d", &arr2[n2]) == 1) {
        n2++;
    }

    fclose(file2);

   

    printf("\nTiempo de ejecución en segundos al ordenar valores en orden aleatorio:\n\n");
    printf("Algoritmo\t\t1k\t  10k\t\t100k\n");
    
 
    for (int i = num_opciones - 1; i >= 0; i--) {
        switch (opciones_ingresadas[i]) {
            case 1:
                medirTiempoA(insertionSort, arr0, arr1, arr2, n0, n1, n2, "Insertion Sort");
                break;
            case 2:                
                medirTiempoA(selectionSort, arr0, arr1, arr2, n0, n1, n2, "Selection Sort");
                break;
            case 3:                
                medirTiempoB(mergeSort, arr0, arr1, arr2, 0, n0-1, n1-1, n2-1, "Merge Sort");
                break;
            case 4:
               medirTiempoB(quickSort, arr0, arr1, arr2, 0, n0-1, n1-1, n2-1, "Quick Sort");
                break;
            case 5:
                medirTiempoA(heapSort, arr0, arr1, arr2, n0, n1, n2, "Heap Sort");
                break;
            case 6:
                medirTiempoA(countingSort, arr0, arr1, arr2, n0, n1, n2, "Counting Sort");
                break;
            case 7:
                medirTiempoA(radixSort, arr0, arr1, arr2, n0, n1, n2, "Radix Sort");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }

     ///

    FILE *file3 = fopen("data/valores_1k_o.txt", "r");
    if (file3 == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    int n3 = 0;
    while (fscanf(file3, "%d", &arr0[n3]) == 1) {
        n3++;
    }

    fclose(file3);

    FILE *file4 = fopen("data/valores_10k_o.txt", "r");
    if (file4 == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    int n4 = 0;
    while (fscanf(file4, "%d", &arr1[n4]) == 1) {
        n4++;
    }

    fclose(file4);

    FILE *file5 = fopen("data/valores_100k_o.txt", "r");
    if (file5 == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    int n5 = 0;
    while (fscanf(file5, "%d", &arr2[n5]) == 1) {
        n5++;
    }

    fclose(file5);

     printf("\nTiempo de ejecución en segundos al ordenar valores ordenados:\n\n");
    printf("Algoritmo\t\t1k\t  10k\t\t100k\n");
    
 
    for (int i = num_opciones - 1; i >= 0; i--) {
        switch (opciones_ingresadas[i]) {
            case 1:
                medirTiempoA(insertionSort, arr0, arr1, arr2, n3, n4, n5, "Insertion Sort");
                break;
            case 2:                
                medirTiempoA(selectionSort, arr0, arr1, arr2, n3, n4, n5, "Selection Sort");
                break;
            case 3:                
                medirTiempoB(mergeSort, arr0, arr1, arr2, 0, n3-1, n4-1, n5-1, "Merge Sort");
                break;
            case 4:
               medirTiempoB(quickSort, arr0, arr1, arr2, 0, n3-1, n4-1, n5-1, "Quick Sort");
                break;
            case 5:
                medirTiempoA(heapSort, arr0, arr1, arr2, n3, n4, n5, "Heap Sort");
                break;
            case 6:
                medirTiempoA(countingSort, arr0, arr1, arr2, n3, n4, n5, "Counting Sort");
                break;
            case 7:
                medirTiempoA(radixSort, arr0, arr1, arr2, n3, n4, n5, "Radix Sort");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }

         ///

    FILE *file6 = fopen("data/valores_1k_r.txt", "r");
    if (file6 == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    n3 = 0;
    while (fscanf(file6, "%d", &arr0[n3]) == 1) {
        n3++;
    }

    fclose(file6);

    FILE *file7 = fopen("data/valores_10k_r.txt", "r");
    if (file7 == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    n4 = 0;
    while (fscanf(file7, "%d", &arr1[n4]) == 1) {
        n4++;
    }

    fclose(file7);

    FILE *file8 = fopen("data/valores_100k_r.txt", "r");
    if (file8 == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    n5 = 0;
    while (fscanf(file8, "%d", &arr2[n5]) == 1) {
        n5++;
    }

    fclose(file8);

    printf("\nTiempo de ejecución en segundos al ordenar valores ordenado en orden inverso:\n\n");
    printf("Algoritmo\t\t1k\t  10k\t\t100k\n");
    
 
    for (int i = num_opciones - 1; i >= 0; i--) {
        switch (opciones_ingresadas[i]) {
            case 1:
                medirTiempoA(insertionSort, arr0, arr1, arr2, n3, n4, n5, "Insertion Sort");
                break;
            case 2:                
                medirTiempoA(selectionSort, arr0, arr1, arr2, n3, n4, n5, "Selection Sort");
                break;
            case 3:                
                medirTiempoB(mergeSort, arr0, arr1, arr2, 0, n3-1, n4-1, n5-1, "Merge Sort");
                break;
            case 4:
               medirTiempoB(quickSort, arr0, arr1, arr2, 0, n3-1, n4-1, n5-1, "Quick Sort");
                break;
            case 5:
                medirTiempoA(heapSort, arr0, arr1, arr2, n3, n4, n5, "Heap Sort");
                break;
            case 6:
                medirTiempoA(countingSort, arr0, arr1, arr2, n3, n4, n5, "Counting Sort");
                break;
            case 7:
                medirTiempoA(radixSort, arr0, arr1, arr2, n3, n4, n5, "Radix Sort");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }

     
    return 0;

}