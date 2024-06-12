#include <stdio.h>
#include <math.h>
#include <time.h>

#include "shared_array.h"
#include "initialize_array.c"

int mov=0, comp=0;

//metodos simples, poco codigo, ideal para archivos pequeños//
void selectionsort(int A[], int n){ //la salida no siempre tiene estabilidad, insertion si.
    int i, j, min, aux;

    for (i=0; i < n-1; i++){    //lazo externo O(n)
        min=i;
        for(j = i+1; j<n;j++){  //lazo interno O(n) -> Costo total: O(n2)
            comp=comp+1;
//            printf("A[min],A[j] %d %d", A[min], A[j]);
//            printf("\n");
            if (A[min] > A[j]){  //Comparaciones desde i hasta n-1 (n-i+1), O(n)
                min=j;
            }
        }
        aux = A[min];
        A[min] = A[i];
        A[i] = aux;
        mov=mov+3;     //3 movimientos por cada iteración O(n)
    }
}                       // mov: O(n), comp: O(n2) para todos los casos (mejor&peor).
//archivo no grande, poca comp
//archivo pequeno y registro grand, bastan comparac, mov e costoso, selectionsort indicado, #mov lineal y menor entre todos.


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
   //int A[]={13, 65, 55, 40, 50, 35, 38, 20, 10, 44, 25};
   //int A[]={1, 3, 6, 9, 13, 100, 2};

   int n =sizeof(shared_array)/sizeof(shared_array[0]);


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
//    initialize_reverse_array(shared_array, ARRAY_SIZE);

    printf("Vector inicial: \n");
    printim(shared_array, ARRAY_SIZE);    
    selectionsort(shared_array, ARRAY_SIZE);
    printf("Resultado del ordenamiento: \n");
    printim(shared_array, ARRAY_SIZE);

   printf("Movimentaciones: %d", mov);
   printf("\n");
   printf("Comparaciones: %d", comp);
   printf("\n");

   end_t = clock();
   
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("%f\n", total_t  );
//   printf("Exiting of the program...\n");

   return 0;
}