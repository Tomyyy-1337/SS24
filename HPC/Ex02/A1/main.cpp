#include <iostream>
#include <chrono>
#include <cmath>
#include "axpy.h"


int main() {

    int arr_size = 1e8;

    double a = rand() - (RAND_MAX / 2);
    double * x = new double[arr_size];
    double * y = new double[arr_size];
    for (int i = 0; i < arr_size; i++) {
        x[i] = rand() - (RAND_MAX / 2);
        y[i] = rand() - (RAND_MAX / 2);
    }

    // print the first 10 elements of x and y
    std::cout << "x = [";
    for (int i = 0; i < 10; i++) {
        std::cout << x[i] << ", ";
    }
    std::cout << " ... ]" << std::endl;
    
    int N[10] = {3, 4, 6, 8};
    for (int i = 0; i < 4; i++) {
        int n = pow(10, N[i]);
        auto start = std::chrono::high_resolution_clock::now();
        calc(n, x, y, a);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time for n = " << n << " is " << elapsed.count() << " seconds." << std::endl;
    }
    return 0;
}