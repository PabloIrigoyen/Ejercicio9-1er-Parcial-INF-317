#include "stdio.h"
#include "stdlib.h"
#include "mpi.h"

void generarPares(int *serie, int inicio, int fin, int incremento, int N) {
    for (int i = inicio; i <= fin; i += incremento) {
        *serie++ = i;
    }
}

int main(int argc, char *argv[]) {
    int ran, tam;
    const int M = 4; 
    const int N = 10;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ran);
    MPI_Comm_size(MPI_COMM_WORLD, &tam);
    if (tam != M) {
        printf("Este programa debe ejecutarse con exactamente %d procesos.\n", M);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int *vectores[M];
    int ini, fin, inc;
    ini = (ran * 2) + 2;
    fin = ini + (N - 1) * M;
    inc = 2 * M;

    vectores[ran] = (int *)malloc(N * sizeof(int));
    generarPares(vectores[ran], ini, fin, inc, N);
    printf("Proceso %d: ", ran);
    for (int i = 0; i < N; ++i) {
        if(vectores[ran][i]>0 && vectores[ran][i]<100000){
           printf("%d ", vectores[ran][i]);
        }
    }
    printf("\n");
    free(vectores[ran]);
    MPI_Finalize();
    return 0;
}
