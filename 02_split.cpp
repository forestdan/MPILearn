#include<cstdio>
#include"mpi.h"

int main(int argc, char** argv) {
    const int N = 18;
    int x0[N];
    int size, rank;
    for (int i = 0; i < N; i++) {
        x0[i] = 99;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int begin = rank * (N / size);
    int end = (rank + 1) * (N / size);
    for (int i = begin; i < end; i++) {
        x0[i] = i;
    }
    printf("%d %d %d ", rank, begin, end);
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d ", x0[i]);
    }
    printf("]\n");
    MPI_Finalize();
}