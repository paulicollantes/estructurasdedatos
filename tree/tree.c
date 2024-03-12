#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Estructura del nodo  BST
struct Node {
    int data;
    struct Node *left, *right;
};

// Estructura del nodo  AVL
struct AVLNode {
    int data;
    struct AVLNode *left, *right;
    int height;
};


// Calcular altura
int height(struct AVLNode *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Estructura del nodo tabla hash
struct HashNode {
    int data;
    struct HashNode *next;
};

// Estructura para la tabla hash
struct HashTable {
    int size;
    struct HashNode **table;
};

// Insertar en BST
struct Node *insertBST(struct Node *root, int value) {
    if (root == NULL) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (value < root->data)
        root->left = insertBST(root->left, value);
    else if (value > root->data)
        root->right = insertBST(root->right, value);

    return root;
}

// Buscar en BST
struct Node *searchBST(struct Node *root, int value, int *count) {
    if (root == NULL) {
        *count = 0;
        return root;
    }

    if (value == root->data) {
        *count = 1;
        return root;
    }

    if (value < root->data)
        return searchBST(root->left, value, count);

    struct Node *rightResult = searchBST(root->right, value, count);
    *count += (rightResult != NULL) ? *count : 0;

    return rightResult;
}

// Rotación derecha AVL
struct AVLNode *rightRotate(struct AVLNode *y) {
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotación izquierda AVL
struct AVLNode *leftRotate(struct AVLNode *x) {
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


// Insertar en AVL
struct AVLNode *insertAVL(struct AVLNode *root, int value){
    if (root == NULL) {
        struct AVLNode *newNode = (struct AVLNode *)malloc(sizeof(struct AVLNode));
        newNode->data = value;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (value < root->data)
        root->left = insertAVL(root->left, value);
    else if (value > root->data)
        root->right = insertAVL(root->right, value);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = height(root->left) - height(root->right);

    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Buscar en AVL
struct AVLNode *searchAVL(struct AVLNode *root, int value, int *count) {
    if (root == NULL) {
        *count = 0;
        return root;
    }

    if (value == root->data) {
        *count = 1;
        return root;
    }

    if (value < root->data)
        return searchAVL(root->left, value, count);

    struct AVLNode *rightResult = searchAVL(root->right, value, count);
    *count += (rightResult != NULL) ? *count : 0;

    return rightResult;
}

int hashFunction(int key, int size) {
    return (key % size);
}

// Insertar en tabla hash
void insertHash(struct HashTable *hashTable, int value) {
    int index = hashFunction(value, hashTable->size);
    struct HashNode *newNode = (struct HashNode *)malloc(sizeof(struct HashNode));
    newNode->data = value;
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

// Buscar en tabla hash
bool searchHash(struct HashTable *hashTable, int value, int *count) {
    int index = hashFunction(value, hashTable->size);
    struct HashNode *current = hashTable->table[index];
    while (current != NULL) {
        if (current->data == value) {
            *count = 1;
            return true;
        }
        current = current->next;
        *count += 1;
    }
    *count = 0;
    return false;
}

// Calcular el tiempo de ejecución de búsqueda e inserción
void measureTime(struct Node *(*insertFunctionBST)(struct Node *, int), 
                 struct Node *(*searchFunctionBST)(struct Node *, int, int *), 
                 struct AVLNode *(*insertFunctionAVL)(struct AVLNode *, int), 
                 struct AVLNode *(*searchFunctionAVL)(struct AVLNode *, int, int *), 
                 void (*insertFunctionHash)(struct HashTable *, int), 
                 bool (*searchFunctionHash)(struct HashTable *, int, int *),
                 int operationCount, int searchValue) {
    
    // Tiempo de inserción en BST
    struct Node *bstRoot = NULL;
    clock_t start = clock();
    for (int i = 0; i < operationCount; i++) {
        bstRoot = insertFunctionBST(bstRoot, i);
    }
    clock_t end = clock();
    if (operationCount >= 10000) {
        printf("|   BST         | INSERCIÓN     | %d \t |   %f     |\n", operationCount, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
    else{
        printf("|   BST         | INSERCIÓN     | %d \t\t |   %f     |\n", operationCount, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
    

    // Tiempo de búsqueda en BST
    int countBST = 0;
    start = clock();
    struct Node *resultBST = searchFunctionBST(bstRoot, searchValue, &countBST);
    end = clock();
    printf("|   BST         | BÚSQUEDA      | \t\t |   %f     |\n", ((double)(end - start)) / CLOCKS_PER_SEC);


    // Tiempo de inserción en AVL
    struct AVLNode *avlRoot = NULL;
    start = clock();
    for (int i = 0; i < operationCount; i++) {
        avlRoot = insertFunctionAVL(avlRoot, i);
    }
    end = clock();
    if (operationCount >= 10000) {
        printf("|   AVL         | INSERCIÓN     | %d \t |   %f     |\n", operationCount, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
    else{
        printf("|   AVL         | INSERCIÓN     | %d \t\t |   %f     |\n", operationCount, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
    
    
    // Tiempo de búsqueda en AVL
    int countAVL = 0;
    start = clock();
    struct AVLNode *resultAVL = searchFunctionAVL(avlRoot, searchValue, &countAVL);
    end = clock();
    printf("|   AVL         | BÚSQUEDA      | \t\t |   %f     |\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    
    
    // Tiempo de inserción en tabla hash
    struct HashTable hashTable;
    hashTable.size = 2 * operationCount; 
    hashTable.table = (struct HashNode **)malloc(sizeof(struct HashNode *) * hashTable.size);
    for (int i = 0; i < hashTable.size; i++) {
        hashTable.table[i] = NULL;
    }

    start = clock();
    for (int i = 0; i < operationCount; i++) {
        insertFunctionHash(&hashTable, i);
    }
    end = clock();
    if (operationCount >= 10000) {
        printf("|   HASH        | INSERCIÓN     | %d \t |   %f     |\n", operationCount, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
    else{
        printf("|   HASH        | INSERCIÓN     | %d \t\t |   %f     |\n", operationCount, ((double)(end - start)) / CLOCKS_PER_SEC);
    }
    
    
    // Tiempo de búsqueda en tabla hash
    int countHash = 0;
    start = clock();
    bool resultHash = searchFunctionHash(&hashTable, searchValue, &countHash);
    end = clock();
    printf("|   HASH        | BÚSQUEDA      | \t\t |   %f     |\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    

    // Liberar memoria de la tabla hash
    for (int i = 0; i < hashTable.size; i++) {
        struct HashNode *current = hashTable.table[i];
        while (current != NULL) {
            struct HashNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable.table);


}


void processFiles(const char *fileNames[], int operationCounts[], int searchValues[][6], int fileCount, const char *typeFiles[]) {
    for (int i = 0; i < fileCount; i++) {
        FILE *file = fopen(fileNames[i], "r");
        if (file == NULL) {
            perror("Error al abrir el archivo");
            return;
        }

        printf("\nTiempos de búsqueda de datos %s:\n\n", typeFiles[i]);
        printf("|   Algoritmo   | Operación     | # Valores      |   Segundos     |\n");

        int value;
        int totalValues = 0;
        int operationIndex = 0;

        while (fscanf(file, "%d", &value) == 1) {
            totalValues++;

            if (totalValues == operationCounts[operationIndex]) {
                measureTime(insertBST, searchBST, insertAVL, searchAVL, insertHash, searchHash,
                            totalValues, searchValues[i][operationIndex]);
                operationIndex++; 
            }
        }

        fclose(file);
    }
}


int main() {
    const char *fileNames[] = {"data/datos.txt", "data/datos_o.txt", "data/datos_r.txt"};
    const char *typeFiles[] = {"en orden aleatorio", "ordenados", "en orden inverso"};
    int operationCounts[] = {1000, 2000, 10000, 11000, 90000, 100000};
    int **searchValues[] = {NULL, NULL, NULL};

    // Asignar memoria para searchValues
    for (int i = 0; i < 3; i++) {
        searchValues[i] = (int **)malloc(6 * sizeof(int *));
        if (searchValues[i] == NULL) {
            perror("Error al asignar memoria para searchValues");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < 6; j++) {
            searchValues[i][j] = (int *)malloc(sizeof(int));
            if (searchValues[i][j] == NULL) {
                perror("Error al asignar memoria para searchValues[i][j]");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Valores de búsqueda 
    *(searchValues[0][0]) = 18276418;
    *(searchValues[0][1]) = 9134827;
    *(searchValues[0][2]) = 19162069;
    *(searchValues[0][3]) = 5263847;
    *(searchValues[0][4]) = 13804092;
    *(searchValues[0][5]) = 27000000;

    *(searchValues[1][0]) = 12047030;
    *(searchValues[1][1]) = 9134827;
    *(searchValues[1][2]) = 12780008;
    *(searchValues[1][3]) = 5263847;
    *(searchValues[1][4]) = 13804092;
    *(searchValues[1][5]) = 21173187;

    *(searchValues[2][0]) = 24951590;
    *(searchValues[2][1]) = 9134827;
    *(searchValues[2][2]) = 24196624;
    *(searchValues[2][3]) = 5263847;
    *(searchValues[2][4]) = 15784971;
    *(searchValues[2][5]) = 27000000;

    int fileCount = sizeof(fileNames) / sizeof(fileNames[0]);

    processFiles(fileNames, operationCounts, searchValues, fileCount, typeFiles);

    // Liberar la memoria asignada para searchValues
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            free(searchValues[i][j]);
        }
        free(searchValues[i]);
    }

    return 0;
}


