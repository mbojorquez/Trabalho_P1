#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "shared_array.h"
#include "initialize_array.c"

int total_shifts = 0;
int total_comparisons = 0;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    total_shifts=total_shifts+3; // Increment total shift counter
}

int partition_pivot_last(int array[], int low, int high) {
    int pivot = array[high]; 
    total_shifts=total_shifts+1;
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        total_comparisons++; // Increment total comparison counter
        if (array[j] < pivot) {
            swap(&array[++i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

int partition_pivot_median(int array[], int low, int high) {
    int pivot;
    int mid = (low + high) / 2;
    if (array[mid] < array[low])
        swap(&array[mid], &array[low]);
    if (array[high] < array[low])
        swap(&array[high], &array[low]);
    if (array[high] < array[mid])
        swap(&array[high], &array[mid]);
        swap(&array[mid], &array[high-1]);
    pivot = array[high-1];
    total_shifts=total_shifts+1;
    return partition_pivot_last(array, low, high);
}

void quickSort_ordena(int array[], int low, int high) { 
    if (low < high) {
        int pi = partition_pivot_median(array, low, high);
        // Sort the elements on the left of pivot
        quickSort_ordena(array, low, pi - 1);
        // Sort the elements on the right of pivot
        quickSort_ordena(array, pi + 1, high);
        }
}

void quicksort(int A[], int n){
    quickSort_ordena(A,0,n-1);
}

void printArray(int A[], int n){
    int i;
    for (i=0;i<n;i++)
        printf("%d ", A[i]);
    printf("\n");
//    printf("n es: %i\n", n);   
}

int main(){
   clock_t start_t, end_t;
   double total_t;
   int i;

   start_t = clock();    
   //int A[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
   //int shared_array[]={13, 65, 55, 40, 50, 35, 38, 20, 10, 44, 25};
   //int A[]={13,65,55,40};
    int n =sizeof(shared_array)/sizeof(shared_array[0]);

//ALEATORY
//    initialize_array(shared_array, ARRAY_SIZE);    
//    srand((unsigned)time(NULL));
//    shuffle(shared_array, ARRAY_SIZE);

//Nearly Sorted - 0.30% aleatory
//    srand((unsigned)time(NULL));
//    initialize_array(shared_array, ARRAY_SIZE);
//    shuffle_last_portion(shared_array, ARRAY_SIZE, UNSORTED_PERCENT);

//Sorted
//    initialize_array(shared_array, ARRAY_SIZE);

//Reverse Sorted
   initialize_reverse_array(shared_array, ARRAY_SIZE);

    printf("Vector inicial: \n");
    printim(shared_array, ARRAY_SIZE);    
    quicksort(shared_array, ARRAY_SIZE);
    printf("Resultado del ordenamiento: \n");
    printim(shared_array, ARRAY_SIZE);

   printf("Movimentaciones: %d", total_shifts);
   printf("\n");
   printf("Comparaciones: %d", total_comparisons);
   printf("\n");

   end_t = clock();
   
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//   printf("Time: %f\n", total_t  );
    printf("%f\n", total_t);
//   printf("Exiting of the program...\n");

   return 0;
}