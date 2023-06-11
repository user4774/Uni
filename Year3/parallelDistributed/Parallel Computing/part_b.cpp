#include "omp.h"
#include <iostream>
#include <random>
#include <string.h>


#define N 50

/* Function for displaying particles on terminal
 *
 * @Params Vector of particles to be printed out */
void showParticles(int particles[10][3]) {
	std::cout << '{';
        for (int i = 0; i < 10; i++) {		//Iterate over particles
		if (i > 0) {
			std::cout << ", ";
		}
                std::cout << '{';
                for (int j = 0; j < 3; j++) {	//Iterate over particle xiz positions
			if (j != 2) {
				std::cout << particles[i][j] << ", ";	
			} else {
				std::cout << particles[i][j];
			}
                }   
                std::cout << '}';
        }   
        std::cout << '}' << std::endl;
}

int main() {
	/* Functionality to move particles away from their starting location at randomly generated speeds and then display their positions */
        int particles[10][3] = {{5, 14, 10}, {7, -8, -14}, {-2, 9, 8}, {15, -6, 3}, {12, 4, -5}, {4, 20, 17}, {-16, 5, -1}, {-11, 3, 16}, {3, 10, -19}, {-16, 7, 4}};
        int PPA = 2;
        std::random_device r; 
        std::mt19937 generator(r());		//Create random number generator mersenne twister
	std::uniform_int_distribution<int> PPADist(1, 5);	//Limit randomly generated values to be between specified values
	std::uniform_int_distribution<int> xyzDist(0, 1);
	int allParticles[3][10][3];
	memcpy(allParticles[0], particles, sizeof(particles));		//Copy array of particles to allParticles for displaying later
	int i = 0;
	for (i = 0; i < N; i++) {
		std::cout << "PPA value: " << PPA << std::endl;
		if (i == 25) {
                        memcpy(allParticles[1], particles, sizeof(particles));
                }

		#pragma omp parallel for		//Defines parallel section, which in this case is a for loop over particles
		for (int j = 0; j < 10; j++) {
			int x = (xyzDist(generator) == 0) ? -1 : 1;	//If random number generator generates a 0, then -1, else 1
			int y = (xyzDist(generator) == 0) ? -1 : 1;
			int z = (xyzDist(generator) == 0) ? -1 : 1;
			particles[j][0] += PPA * x;			//Add or subtract PPA value depending on the randomly generated number
			particles[j][1] += PPA * y;
			particles[j][2] += PPA * z;
		}
		PPA += PPADist(generator);		//Add random number between 1-5
	}
	memcpy(allParticles[2], particles, sizeof(particles));
	
	for (int n = 0; n < 3; n++) {
		if (n == 0) {
			std::cout << "Initial state of particles: ";
		} else if (n == 1) {
			std::cout << "State of particles at step 25: ";	
		} else {
			std::cout << "State of particles at step 50: ";	
		}
		showParticles(allParticles[n]);
	}
        return 0;
}

