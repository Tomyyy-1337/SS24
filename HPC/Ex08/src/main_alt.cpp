#include <mpi.h>
#include <iostream>
#include <cstring>
#include <vector>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int N = 10000000;
    const int local_N = N / size;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;
    std::vector<double> local_x;
    std::vector<double> local_z;
    double startTime, endTime;

    local_x.resize(local_N);
    local_z.resize(local_N);

    if (rank == 0) {
        x.resize(N);
        y.resize(N);
        z.resize(N);

        for (int i = 0; i < N; i++) {
            x[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            y[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        } 
        memcpy(z.data(), y.data(), N * sizeof(double));

        // Baseline
        for(int i=0;i<N;i++) y[i]=2.3*x[i]+y[i];

        startTime = MPI_Wtime();

        memcpy(local_x.data(), x.data(), local_N * sizeof(double));
        memcpy(local_z.data(), z.data(), local_N * sizeof(double));
        for (int i = 1; i < size; i++) {
            MPI_Send(x.data() + i * local_N, local_N, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(z.data() + i * local_N, local_N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
        }    
    }

    if (rank != 0) {
        MPI_Recv(local_x.data(), local_N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(local_z.data(), local_N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (int i = 0; i < local_N; i++) {
        local_z[i] = 2.3 * local_x[i] + local_z[i];
    }


    if (rank != 0) {
        MPI_Send(local_z.data(), local_N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        memcpy(z.data(), local_z.data(), local_N * sizeof(double));
        for (int i = 1; i < size; i++) {
            MPI_Recv(z.data() + i * local_N, local_N, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        endTime = MPI_Wtime();
        std::cout << "Ausführungszeit: " << (endTime - startTime) << " Sekunden." << std::endl;

        // Überprüfung der Korrektheit
        for (int i = 0; i < N; i++) {
            if (y[i] != z[i]) {
                std::cout << "Fehler bei der Überprüfung!" << std::endl;
                break;
            }   
        }
    }

    MPI_Finalize();
    return 0;
}	