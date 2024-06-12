#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "shared_array.h"
#include "initialize_array.c"

//int comp = 0; // Counter for comparisons
long long int mov = 0; // Counter for comparisons
long long int comp = 0; // Counter for total comparisons

// Structure for stack node
struct stacknode {
    int data;
    struct stacknode* next;
};

// Function to create a new stack node
struct stacknode* newnode(int data) {
    struct stacknode* newNode = (struct stacknode*)malloc(sizeof(struct stacknode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to push an element onto the stack
void push(struct stacknode** root, int data) {
    struct stacknode* newNode = newnode(data);
    newNode->next = *root;
    *root = newNode;
}

// Function to pop an element from stack
int pop(struct stacknode** root) {
    if (*root == NULL)
        return -1;
    struct stacknode* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

// Function to get the minimum value from the stack
int getmin(struct stacknode* root) {
    if (root == NULL)
        return -1;
    return root->data;
}

void printStacks(struct stacknode* pileStacks[], int piles) {
    printf("Formed Stacks:\n");
    for (int i = 0; i < piles; i++) {
        printf("Stack %d:", i + 1);
        struct stacknode* current = pileStacks[i];
        while (current != NULL) {
            printf(" %d", current->data);
            current = current->next;
        }
        printf("\n");
    }
}


// Function to perform patience sort
void patiencesort(int arr[], int n) {
    struct stacknode* pileStacks[n];
    int piles = 0;
    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < piles; j++) {
            comp++;
            if (arr[i] <= getmin(pileStacks[j])) {
                push(&pileStacks[j], arr[i]);
                mov++;
                break;
            }
        }
        if (j == piles) {
            pileStacks[piles] = newnode(arr[i]);
            piles++;
            mov++;
        }
        comp++;
    }

    // Print formed stacks
    printStacks(pileStacks, piles);
//construye el vector ordenado
    int sortedIndex = 0;
    while (sortedIndex < n) {
        int minPile = -1;
        for (int i = 0; i < piles; i++) {
            comp++;
            if (pileStacks[i] != NULL && (minPile == -1 || getmin(pileStacks[i]) < getmin(pileStacks[minPile])))
                minPile = i;

        }
        arr[sortedIndex++] = pop(&pileStacks[minPile]);
        mov++;      
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    //int arr[] = {13, 65, 55, 40, 50, 35, 38, 20, 10, 44, 25};
    int n = sizeof(shared_array) / sizeof(shared_array[0]);

//ALEATORY
    initialize_array(shared_array, ARRAY_SIZE);    
    srand((unsigned)time(NULL));
    shuffle(shared_array, ARRAY_SIZE);

//Nearly Sorted - 0.30% aleatory
//    initialize_array(shared_array, ARRAY_SIZE);
//    srand((unsigned)time(NULL));
//    shuffle_last_portion(shared_array, ARRAY_SIZE, UNSORTED_PERCENT);

//Sorted
//   initialize_array(shared_array, ARRAY_SIZE);

//Reverse Sorted
//   initialize_reverse_array(shared_array, ARRAY_SIZE);

    printf("Vector inicial: \n");
    printArray(shared_array, ARRAY_SIZE);    
    patiencesort(shared_array, ARRAY_SIZE);
    printf("Resultado del ordenamiento: \n");
    printim(shared_array, ARRAY_SIZE);


    printf("Movimentaciones: %lld", mov);
    printf("\n");
    printf("Comparaciones: %lld", comp);
    printf("\n");

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//    printf("%f\n", total_t);
    printf("Total time taken by CPU: %f seconds\n", total_t);

    return 0;
}
