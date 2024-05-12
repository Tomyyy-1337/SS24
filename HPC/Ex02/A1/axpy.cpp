void calc(int arr_size, double *x, double *y, double a) {
    for (int i = 0; i < arr_size; i++) {
        y[i] = a * x[i] + y[i];
    }
}