# include "benchmark_function.h"
# include <unistd.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <sys/time.h>
# include <stdlib.h>
# include <sys/time.h>

static ssize_t STREAM_ARRAY_SIZE = 100000000;

#define NTIMES	20

# define HLINE "-------------------------------------------------------------\n"

# ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
# endif
# ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
# endif

# define STREAM_TYPE double
# define MESSUREMENT_COUNT 11

static double avgtime[MESSUREMENT_COUNT] = {0}, 
		maxtime[MESSUREMENT_COUNT] = {0},
		mintime[MESSUREMENT_COUNT],
		bytes[MESSUREMENT_COUNT];

extern double mysecond();
extern double fRand(double fMin, double fMax);

int main() {
	//Initialization

    int			BytesPerWord;
    int			k;
    ssize_t		i,j;
    double		t, times[MESSUREMENT_COUNT][NTIMES];

	STREAM_TYPE *x = (STREAM_TYPE *) malloc(STREAM_ARRAY_SIZE * sizeof(STREAM_TYPE));
	STREAM_TYPE *y = (STREAM_TYPE *) malloc(STREAM_ARRAY_SIZE * sizeof(STREAM_TYPE));
	ssize_t *number = (ssize_t *) malloc(MESSUREMENT_COUNT * sizeof(ssize_t));

	for (int i = 1; i < MESSUREMENT_COUNT; i++) {
		number[i] = i * 1e7;
	}
	number[0] = 1e6;
	for (int i = 0; i < MESSUREMENT_COUNT; i++) {
		bytes[i] = 3 * sizeof(STREAM_TYPE) * number[i];
		mintime[i] = FLT_MAX;
	}

	for (int i = 0; i < STREAM_ARRAY_SIZE; i++) {
		x[i] = fRand(1, 100);
		y[i] = fRand(1, 100);
	}

    printf(HLINE);
    printf("Starting Benchmark:\n");
    printf(HLINE);

	// Benchmarking

	for (int j = 0; j < MESSUREMENT_COUNT; j++) {
	
		for (k=0; k<NTIMES; k++) {
			times[j][k] = mysecond();

			calc(number[j], x, y);

			times[j][k] = mysecond() - times[j][k];
		}

	}

    // Print Results

    for (k=1; k<NTIMES; k++) {
		for (j=0; j<MESSUREMENT_COUNT; j++) {
			avgtime[j] = avgtime[j] + times[j][k];
			mintime[j] = MIN(mintime[j], times[j][k]);
			maxtime[j] = MAX(maxtime[j], times[j][k]);
	    }
	}
    
    printf("Input Size  Best Rate MB/s  Avg Rate MB/s  Avg time     Min time     Max time\n");
    for (j=0; j<MESSUREMENT_COUNT; j++) {
		avgtime[j] = avgtime[j]/(double)(NTIMES-1);

		printf("%10.d %12.1f  %12.1f  %11.6f  %11.6f  %11.6f\n",
		   number[j],
	       1.0E-06 * bytes[j]/mintime[j],
	       1.0E-06 * bytes[j]/avgtime[j],
	       avgtime[j],
	       mintime[j],
	       maxtime[j]);
    }
    printf(HLINE);

    return 0;
}

double mysecond() {
	struct timeval tp;
	struct timezone tzp;
	int i;

	i = gettimeofday(&tp,&tzp);
	return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

// Random number generator
double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}