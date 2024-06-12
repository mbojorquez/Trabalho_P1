#include <stdio.h>
#include <math.h>
#include <time.h>

#include "shared_array.h"
#include "initialize_array.c"

long long int mov=0;
long long int comp=0;

void bublesort(int A[], int n){ //algoritmo simple y estable, porque compara siempre 2 posiciones
    int i, j, aux, troca;

    for (i=0; i < n-1; i++){    //lazo externo O(n)
        troca=0;                //para mejorar el algoritmo
        for(j = 1; j<n-i;j++){   //lazo interno O(n) -> Costo total: O(n2)
            comp=comp+1;
//            printf("A[j],A[j-1] %d %d\n", A[j], A[j-1]);
//            printf("\n");
            if (A[j] < A[j-1]){  //O(n2) # de comparaciones
                aux = A[j];
                A[j] = A[j-1];
                A[j-1] = aux;     //3 moviment para cada caso verdadero M(n)<=3C(n) entao M(n)=O(n2)
                troca=1;
                mov=mov+3;
            }
        }
        if (troca==0)           //para mejorar el algortimo
            break;
    }
}            // 

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
//    initialize_array(shared_array, ARRAY_SIZE);    
//    srand((unsigned)time(NULL));
//    shuffle(shared_array, ARRAY_SIZE);

//Nearly Sorted - 0.30% aleatory
    initialize_array(shared_array, ARRAY_SIZE);
    srand((unsigned)time(NULL));
    shuffle_last_portion(shared_array, ARRAY_SIZE, UNSORTED_PERCENT);

//Sorted
//   initialize_array(shared_array, ARRAY_SIZE);

//Reverse Sorted
//   initialize_reverse_array(shared_array, ARRAY_SIZE);

    printf("Vector inicial: \n");
    printim(shared_array, ARRAY_SIZE);    
    bublesort(shared_array, ARRAY_SIZE);
    printf("Resultado del ordenamiento: \n");
    printim(shared_array, ARRAY_SIZE);

   printf("Movimentaciones: %lld", mov);
   printf("\n");
   printf("Comparaciones: %lld", comp);
   printf("\n");

   end_t = clock();
   
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//   printf("%f\n", total_t  );
   printf("Total time taken by CPU: %f\n", total_t  );
//   printf("Exiting of the program...\n");

   return 0;
}