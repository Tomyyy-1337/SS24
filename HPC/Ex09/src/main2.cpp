#include <mpi.h>
#include <iostream>
#include <cstring>
#include <vector>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<double> x;
    double startTime, endTime;
    int message_tag = 0;
    double message_var = 0;
    MPI_Request request;

    double two_way_delay = 0.0;
    double one_way_delay = 0.0;

    const int sizes[] = {1000, 10000, 20000, 40000, 60000, 80000, 100000, 200000, 400000, 600000, 800000, 1000000, 2000000, 4000000, 6000000, 8000000, 10000000, 100000000};
    
    // Calculate delay for message
    if (rank == 0) {
        // Send additional messages because the first message has shown to be slower
        MPI_Send(&message_var, 1, MPI_DOUBLE, 1, message_tag++, MPI_COMM_WORLD);
        MPI_Recv(&message_var, 1, MPI_DOUBLE, 1, message_tag++, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        two_way_delay = MPI_Wtime();
        MPI_Send(&message_var, 1, MPI_DOUBLE, 1, message_tag++, MPI_COMM_WORLD);
        MPI_Recv(&message_var, 1, MPI_DOUBLE, 1, message_tag++, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        two_way_delay = MPI_Wtime() - two_way_delay;
        one_way_delay = two_way_delay / 2.0;
        std::cout << "One way delay: " << one_way_delay << std::endl;
    } else if (rank == 1) {
        MPI_Recv(&message_var, 1, MPI_DOUBLE, 0, message_tag++, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&message_var, 1, MPI_DOUBLE, 0, message_tag++, MPI_COMM_WORLD);
        MPI_Recv(&message_var, 1, MPI_DOUBLE, 0, message_tag++, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&message_var, 1, MPI_DOUBLE, 0, message_tag++, MPI_COMM_WORLD);
    }

    // Measure time for data transfer
    if (rank == 0) {
        std::cout << "Size | Time | Time - One way delay" << std::endl;
        for (int s: sizes) {
            x.resize(s);
            for (int i = 0; i < s; i++) {
                x[i] = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            } 

            startTime = MPI_Wtime();


            MPI_Isend(x.data(), s, MPI_DOUBLE, 1, message_tag++, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            MPI_Recv(&message_var, 1, MPI_DOUBLE, 1, message_tag++, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            endTime = MPI_Wtime();

            double delta_time = endTime - startTime;

            std::cout << s << " " << delta_time << " " << delta_time - one_way_delay << std::endl;
        }
    } else if (rank == 1) {
        for (int s: sizes) {
            x.resize(s);
            MPI_Irecv(x.data(), s, MPI_DOUBLE, 0, message_tag++, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            MPI_Send(&message_var, 1, MPI_DOUBLE, 0, message_tag++, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}	