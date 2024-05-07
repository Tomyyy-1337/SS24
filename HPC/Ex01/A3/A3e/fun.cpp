#include <math.h>

void calc(int arr_size, int *arr)
{
    int max = 0;
    for (int iter = 0; iter < 1000; iter++)
    {
        for (int i = 0, max = 0; i < arr_size; i++)
            if (fabs(arr[i]) > max)
                max = fabs(arr[i]);
        arr[iter] = max - 1;
    }
}