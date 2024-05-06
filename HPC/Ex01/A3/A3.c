#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {
    clock_t start, end;
    long seconds; 

    start = clock();

    int arr_size = pow(10, 6);

    int * arr =  (int *) malloc(arr_size * sizeof(int));

    for (int i = 0; i < arr_size; i++) {
        arr[i] = rand() - (RAND_MAX / 2);
    }

    int max = 0;
    for (int iter = 0; iter < 1000; iter++) {
        for (int i = 0, max = 0;i<arr_size;i++)
        if(fabs(arr[i])>max) max=fabs(arr[i]);
        arr[iter] = max-1;
    }

    end = clock();
    seconds = ((long)end - (long)start)/CLOCKS_PER_SEC;
    
    printf("Time taken: %.9fs\n", seconds);
    #ifdef __GNUC__
    	printf ("Compiler: Gcc Version %d.%d\n", __GNUC__, __GNUC_MINOR__);
	#endif
    free(arr);

    return 0;
}