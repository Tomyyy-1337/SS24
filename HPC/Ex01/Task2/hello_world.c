#include <stdio.h>
#include <math.h>

int main() {
	#ifdef __GNUC__
    	printf ("Hello World! \nCompiler: Gcc Version %d.%d\n", __GNUC__, __GNUC_MINOR__);
	#endif

	return 0;
}
