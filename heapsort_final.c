#include <stdio.h>
#include <math.h>
#include <time.h>

#include "shared_array.h"
#include "initialize_array.c"

int comp=0, mov=2;

//heaprefaz utilizando metodo iterativo apoyado en un "aux", no recursivo
void heaprefaz(int A[], int left, int right){
    int i, j, aux;
    i=left;
    j=i*2+1;
    aux=A[i];
    while (j <= right){
        comp=comp+2;
        mov=mov+1;
        if ((j<right) && (A[j]<A[j+1])) 
            j++;
        if (aux >= A[j])    // 2 comparaciones
            break;
        A[i]=A[j]; //unica movimentacion (h->logn)
        i=j;
        j=i*2+1;
    }
    A[i]=aux;//Comparaciones O(h) pero con menos movimentacoes; h: altura del arbol es <= logn
}//comparaciones: C(h) es 2h -> O(h) -> O(logn)
//movimentaciones es 2+h     -> O(h) -> O(logn)

void heapconstroi(int A[], int n){
    int left;
    left = (n/2)-1;
    while (left>=0){
        heaprefaz(A, left, n-1);
        left--;
    }
}

void heapsort(int A[], int n){
    int m, aux;
    heapconstroi(A,n);  //O(n) en el peor caso
    m=n-1;
    while (m>0){        //repeticiones O(m)=O(n)
        aux=A[m];
        A[m]=A[0];
        A[0]=aux;
        m=m-1;
        heaprefaz(A,0,m);   // refaz O(lg m)= O(lg n); total= O(nlgn)
    }//metodo no estable, es in place, no demanda memoria adicional, costo siempre es O(nlgn)
    //cualquier sea el tamaño de la entrada, no recomendado para pocos registros por el costo de construir el heap.
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
//  initialize_array(shared_array, ARRAY_SIZE);

//Reverse Sorted
   initialize_reverse_array(shared_array, ARRAY_SIZE);

    printf("Vector inicial: \n");
    printim(shared_array, ARRAY_SIZE);    
    heapsort(shared_array, ARRAY_SIZE);
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