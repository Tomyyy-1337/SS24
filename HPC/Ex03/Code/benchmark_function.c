# include <stdio.h>

void calc(ssize_t N, double* x, double* y) {
    for(ssize_t i=0;i<N;i++) 
        y[i]=2.3*x[i]+y[i];
}