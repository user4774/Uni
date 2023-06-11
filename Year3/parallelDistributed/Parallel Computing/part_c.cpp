#include "omp.h"
#include <iostream>
#include <vector>	
#include <random>
#include <string.h>


#define N 50


/* Function to print vector of particles to the screen
 *
 * @Params vector of particles to be printed
 */
void showParticles(std::vector<std::vector<int>> particles) {
	std::cout << '{';
        for (int i = 0; i < 10; i++) {		//Iterate over all particles
		if (i > 0) {
			std::cout << ", ";
		}
                std::cout << '{';
                for (int j = 0; j < 3; j++) {	//Iterate over particle xyz coords
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

/* Function to get distance from centroid of particle
 *
 * @Params Vector of particles, Vector of centroid of particles
 */
void showDistance(std::vector<std::vector<int>> particles, std::vector<int> centroid) {
	std::vector<std::vector<int>> distance(10, std::vector<int>(3));	//Create vector to add values of distance from centroid to
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 3; j++) {
			distance[i][j] = abs(centroid[j] - particles[i][j]);	//Get absolute value of distance from centroid
		}
	}
	showParticles(distance);
}

/* Get centre of all vectors and return as vector
 *
 * @Return Vector of the centrepoints of particles original position */
std::vector<int> findCentroid() {
        std::vector<std::vector<int>> particles = {{5, 14, 10}, {7, -8, -14}, {-2, 9, 8}, {15, -6, 3}, {12, 4, -5}, {4, 20, 17}, {-16, 5, -1}, {-11, 3, 16}, {3, 10, -19}, {-16, 7, 4}};
	int x = 0;
	int y = 0;
	int z = 0;
	for (int i = 0; i < 10; i++) {		//Loop over particle vector and add up the xyz values
		x += particles[i][0];
		y += particles[i][1];
		z += particles[i][2];
	}
	std::vector<int> centroid = {x / 10, y / 10, z / 10};	//Get the average of xyz values which will become the centroid
	return centroid;
}

/* Function to move particles around in a randomly accelerating way
 *
 * @Return Vector of particles that have been moved for N number of times
 */
std::vector<std::vector<int>> moveParticles() {
        std::vector<std::vector<int>> particles = {{5, 14, 10}, {7, -8, -14}, {-2, 9, 8}, {15, -6, 3}, {12, 4, -5}, {4, 20, 17}, {-16, 5, -1}, {-11, 3, 16}, {3, 10, -19}, {-16, 7, 4}};
        int PPA = 2;
        std::random_device r;		//Initialise random device 
        std::mt19937 generator(r());	//Initialise random device generator mersenne twister
	std::uniform_int_distribution<int> PPADist(1, 5);	//Distribution range for random value generators
	std::uniform_int_distribution<int> xyzDist(0, 1);
	std::vector<std::vector<std::vector<int>>> allParticles;	//Vector to save values to at steps 0, 25 and 50
	allParticles.push_back(particles);
	for (int i = 0; i < N; i++) {		//Iterate over particle vector a set amount of times
		if (i == 25) {
			allParticles.push_back(particles);
                }

		#pragma omp parallel for		//Define parallelizable section, in this case a for loop
		for (int j = 0; j < 10; j++) {		//Iterate over particles all particles in parallel
			int x = (xyzDist(generator) == 0) ? -1 : 1;	//If random number generator gets a 0, set x/y/z value to -1, else set to 1
			int y = (xyzDist(generator) == 0) ? -1 : 1;
			int z = (xyzDist(generator) == 0) ? -1 : 1;
			particles[j][0] += PPA * x;			//Add or subtract PPA value from current particle direction
			particles[j][1] += PPA * y;
			particles[j][2] += PPA * z;
		}
		PPA += PPADist(generator);		//Add a random value from 1-5 to PPA
	}
	allParticles.push_back(particles);
	
        return particles;
}

/* Function to move particles back towards their original centroid positions at accelerating speeds */
void contractParticles(std::vector<std::vector<int>> particles) {
        std::vector<std::vector<int>> oldParticles = {{5, 14, 10}, {7, -8, -14}, {-2, 9, 8}, {15, -6, 3}, {12, 4, -5}, {4, 20, 17}, {-16, 5, -1}, {-11, 3, 16}, {3, 10, -19}, {-16, 7, 4}};
	int PPA = 2;
	std::random_device r;
	std::mt19937 generator(r());
	std::uniform_int_distribution<int> PPADist(1, 5);
	std::uniform_int_distribution<int> xyzDist(0, 1);
	std::vector<std::vector<std::vector<int>>> allParticles;
	std::vector<int> centroid = findCentroid();
	allParticles.push_back(particles);
	std::cout << "Distance 1: ";
	showDistance(particles, centroid);	//Print out initial distance from centroid
	for (int i = 0; i < N; i++) {
		std::cout << "PPA value: " << PPA << std::endl;
		if (i == 25) {
			std::cout << "Distance 2: ";
			showDistance(particles, centroid);
			allParticles.push_back(particles);
                }
		#pragma omp parallel for collapse(2)	//Defining parallel section that collapses both loops into one
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 3; k++) {
				int n = 0;
				if (particles[j][k] > centroid[k]) {		//Check if particles are away from the centroid, if so move them
					n = -1;
				} else if (particles[j][k] < centroid[k]) {
					n = 1;
				}
				particles[j][k] += PPA * n;
			}
		}
		PPA += PPADist(generator);	//Increase PPA value from 1-5
	}
	
	allParticles.push_back(particles);
	std::cout << "Distance 3: ";
	showDistance(particles, centroid);
	std::cout << "Original distance from centre: ";
	showDistance(oldParticles, centroid);
	for (int n = 0; n < 3; n++) {		//Show particles at different steps
		if (n == 0) {
			std::cout << "Particles at step 0: ";
		} else if (n == 1) {
			std::cout << "Particles at step 25: ";
		} else {
			std::cout << "Particles at step 50: ";	
		}
		showParticles(allParticles[n]);
	}
}

int main() {
	std::vector<std::vector<int>> particles = moveParticles();
	contractParticles(particles);
	return 0;
}

