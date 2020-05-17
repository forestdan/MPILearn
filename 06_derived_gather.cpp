#include<cstdio>
#include"mpi.h"

struct Info
{
    int x, y;
};

int main(int argc, char** argv) {
    const int N = 18;
    Info info0[N];
    int size, rank;
    for (int i = 0; i < N; i++) {
        info0[i].x = 99;
        info0[i].y = 99;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int begin = rank * (N / size);
    int end = (rank + 1) * (N / size);
    for (int i = begin; i < end; i++) {
        info0[i].x = i;
        info0[i].y = i * 2;
    }
    Info info[N];
    printf("%d %d %d ", rank, begin, end);
    printf("info0:[");
    for (int i = 0; i < N; i++) {
        printf("{%d, %d},", info0[i].x, info0[i].y);
    }
    printf("]\n");
    MPI_Datatype MYTYPE;
    MPI_Type_contiguous(2, MPI_INT, &MYTYPE);
    // MPI_Type_vector(1, 1, 0, MPI_DOUBLE, &MYTYPE);
    MPI_Type_commit(&MYTYPE);
    MPI_Allgather(&info0[begin], end - begin, MYTYPE, info, end - begin, MYTYPE, MPI_COMM_WORLD);

    printf("%d %d %d ", rank, begin, end);
    printf("info:[");
    for (int i = 0; i < N; i++) {
        printf("{%d, %d},", info[i].x, info[i].y);
    }
    printf("]\n");
    MPI_Finalize();
}