#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "shared_array.h"
#include "initialize_array.c"

//Método mergesort RECURSIVO, no es "in place" porque usa memoria auxiliar
//Merge sort siempre divide el problema de forma balanceada(genera subprobl de forma balanceada)
//Costo de O(nlogn)

int mov=0, comp=0;

//intercala los vectores A[p...q] y A[q...r]
void mergesort_intercala(int A[], int p, int q, int r){
    int i, j, k;
    int *B;
    B=(int*)malloc((r-p+1)*sizeof(int));
    for (i=p; i<=q; i++){//1er lazo, theta(n/2) -> theta(n) operaciones
        B[i-p]=A[i];// theta(n/2) movimentac
        mov=mov+1;
    }
    for (j=q+1; j<=r;j++){//2do lazo, theta(n/2) -> theta (n) operaciones
        B[r+q+1-j-p]=A[j];// theta(n/2) movimentaci; copiando vector a hacia B
        mov=mov+1;
    }
    i=p;
    j=r;
    for (k=p;k<=r;k++){//3er lazo, theta(n)
        comp=comp+1;
        if (B[i-p]<=B[j-p]){ //solo aqui ocurre comparaciones de llaves theta(n)
            A[k]=B[i-p];//Theta (n) movimentaci
            i=i+1;
            mov=mov+1;
        }
        else{
            A[k]=B[j-p];
            j=j-1;
            mov=mov+1;
        }
    }
    free(B);
} //movimentac total: theta(2n) movimentaciones; theta(n) comparaciones

// Viendolo como un arvore, en cada nivel es asintoticamente igual a theta(n)
// la altura del arvore es 1+logn -> O(logn), entonces el algoritmo es O(nlogn)


//ordena el vector de "p" a "r" -> A[p...r]
void mergesort_ordena(int A[], int p, int r){
    int q;
    if (p<r){// aqui me parece que va el (logn), dividirá hasta que p=r, altura logn
        q=(p+r)/2;
        mergesort_ordena(A,p,q);//llamada recursiva T(theta (n/2))
        mergesort_ordena(A,q+1,r);//llamada recursiva T(theta (n/2))
        mergesort_intercala(A,p,q,r);//theta(n)
    }//total tiene un costo de theta (n)
}

//ordena el vector A[0...n-1]
void mergesort(int A[], int n){
    mergesort_ordena(A,0,n-1);
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
   //int A[]={13, 65, 55, 40, 50, 35, 38, 20, 10, 44, 25};
   //int A[]={13,65,55,40};
   int n =sizeof(shared_array)/sizeof(shared_array[0]);

//ALEATORY
//    initialize_array(shared_array, ARRAY_SIZE);    
//    srand((unsigned)time(NULL));
//    shuffle(shared_array, ARRAY_SIZE);

//Nearly Sorted - 0.30% aleatory
//    initialize_array(shared_array, ARRAY_SIZE);
//    srand((unsigned)time(NULL));
//    shuffle_last_portion(shared_array, ARRAY_SIZE, UNSORTED_PERCENT);

//Sorted
//   initialize_array(shared_array, ARRAY_SIZE);

//Reverse Sorted
   initialize_reverse_array(shared_array, ARRAY_SIZE);

    printf("Vector inicial: \n");
    printim(shared_array, ARRAY_SIZE);    
    mergesort(shared_array, ARRAY_SIZE);
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

//desventaja: utiliza memoria auxiliar O(n)
//y en la practica es mas lento q quicksort en caso medio