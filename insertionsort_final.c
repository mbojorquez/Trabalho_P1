#include <stdio.h>
#include <math.h>
#include <time.h>

#include "shared_array.h"
#include "initialize_array.c"

long long int mov=0;
long long int comp=0;

//metodos simples, poco codigo, ideal para archivos pequeños//
void insertionsort(int A[], int n){
    int i, j, aux;

    for (i=1; i < n; i++){
        aux=A[i];   // 1 movimiento x cada iteracion
        j=i-1;
 //       printf("j,aux %d %d", A[j], aux);
 //       printf("\n");
        comp=comp+1;                //cuenta las comparaciones del while (incluye afirmativas)
 //       if ((j>=0) && (A[j] > aux)){//cuenta sólo comparaciones afirmativas del while
 //           count=count+1;    
 //       }                              
        while((j>=0 && (A[j] > aux))){  //Comparaciones depende del orden del array
//            printf("-j, aux %d %d", A[j], aux);
//            printf("\n");
            mov=mov+1;              
            A[j+1]=A[j];                //mejor caso es O(1), peor caso O(n) (#max de veces: i)
            j--;                        //2 movimientos por lazo interno
            comp=comp+1;          //cuenta las comparaciones afirmativas+comparaciones del loop
        }                           //total comparaciones=comp while  + [(comp afirmat+loop) - comp afirmat]
        A[j+1]=aux;
        mov=mov+2; // 1 movimiento por cada iteración
    }               // mejor caso mov&comp: O(n), peor caso O(n2)
}// ideal cuando el archvio esta cuasi ordenado porq hace pocas operaciones.
// por ejemplo al adicionar pocos elementos. insercion estable. 
// in place. demanda solo una variable aux.
// estable porque si es mayor o no disloco (cambio)


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
 //   initialize_array(shared_array, ARRAY_SIZE);    
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
    insertionsort(shared_array, ARRAY_SIZE);
    printf("Resultado del ordenamiento: \n");
    printim(shared_array, ARRAY_SIZE);

   printf("Movimentaciones: %lld", mov);
   printf("\n");
   printf("Comparaciones: %lld", comp);
   printf("\n");

   end_t = clock();
   
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("%f\n", total_t);
//   printf("Exiting of the program...\n");

   return 0;
}