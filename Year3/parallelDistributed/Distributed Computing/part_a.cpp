#include <iostream>
#include <string>    
#include <cstring>
#include <unistd.h>
#include <thread>
#include <sys/sysinfo.h>
#include "mpi.h"


int main(int argc, char** argv) {
	int com_size, rank;		
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &com_size);	//Set comm size on all nodes
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);		//Set comm rank on all nodes
	
	if (rank==0) {	std::cout <<  std::endl; 			//run following section only on head node
		std::cout << "Node Count: " << com_size << std::endl;	//print out all currently active nodes
	}
	std::system("hostname");					//print name of node on terminal
	std::system("cat /proc/cpuinfo | grep MHz");			//grab core clock speed from cpuinfo with grep and display it on each node
	std::system("free -m");						//display RAM information for each node
	MPI_Finalize();
	return 0;
}

