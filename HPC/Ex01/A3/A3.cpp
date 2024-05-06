#include <math.h>
#include <iostream>
#include <chrono>

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    int arr_size = 1e6;
    
    int * arr = new int[arr_size];

    for (int i = 0; i < arr_size; i++) {
        arr[i] = rand() - (RAND_MAX / 2);
    }

    int max = 0;
    for (int iter = 0; iter < 1000; iter++) {
        for (int i = 0, max = 0;i<arr_size;i++)
        if(fabs(arr[i])>max) max=fabs(arr[i]);
        arr[iter] = max-1;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;

    #ifdef __GNUC__
    	printf ("Compiler: Gcc Version %d.%d\n", __GNUC__, __GNUC_MINOR__);
	#endif
    free(arr);

    return 0;
}