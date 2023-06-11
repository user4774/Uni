#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <time.h>

#define THREADS 4

int main() {

	int i, j;	//private and public variables used in the parallel for
	int p = 5;
	#pragma omp parallel for private(j) schedule(static) num_threads(THREADS)	//start of parallel region, with j specified in pragma omp as private (other variables stay public) 
	for (i = 0; i < 3; i++) {							
		for (j = 0; j < 5; j++)
			std::cout << j + p << std::endl;				//print out the addition of public p and private j values.
	}
	return 0;
}
