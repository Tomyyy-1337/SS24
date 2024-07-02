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
    }

    MPI_Scatter(x.data(), local_N, MPI_DOUBLE, local_x.data(), local_N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(z.data(), local_N, MPI_DOUBLE, local_z.data(), local_N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_N; i++) {
        local_z[i] = 2.3 * local_x[i] + local_z[i];
    }

    MPI_Gather(local_z.data(), local_N, MPI_DOUBLE, z.data(), local_N, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    if (rank == 0) {
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