# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <sys/time.h>
# include <stdlib.h>

#ifndef N
#   define N 10000000
#endif

#ifdef _OPENMP
extern int omp_get_num_threads();
#endif


double mysecond()
{
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

int main() {
    int k;
    double time;
    float x[N], y[N];


    #ifdef _OPENMP
    #pragma omp parallel 
        {
    #pragma omp master
        {
            k = omp_get_num_threads();
            printf ("Number of Threads requested = %i\n",k);
            }
        }
    #endif

    #ifdef _OPENMP
        k = 0;
    #pragma omp parallel
    #pragma omp atomic 
            k++;
        printf ("Number of Threads counted = %i\n",k);
    #endif
    
    // fill arrays eith random values
    for(int i=0;i<N;i++) {x[i]=rand() % 100; y[i]=rand() % 100;}

    time = mysecond();
    #pragma omp parallel for
    for(int i=0;i<N;i++) y[i]=2.3*x[i]+y[i];
    time = mysecond()-time;

    printf("elapsed time: %11.6f\n",time);
}