#include <iostream>
#include <string>    
#include <cstring>
#include "mpi.h"
#include <unistd.h>


/* ExampleStruct1 structure to be created, modified and sent between nodes. Variables hold no inherent meaning. */
typedef struct {
	float list[15];
	int size;
	int x;
	int y;
	char letter;
	double number;
} ExampleStruct1;

/* ExampleStruct2 structure to be created, modified and sent between nodes. Variables hold no inherent meaning. */
typedef struct {
	int playerlist[30];
	int playerlistSize;
	int levelNameSize;
	int gameBoardWidth;
	int gameBoardHeight;
	char levelName[50];
	long double randVar;
} ExampleStruct2;

/* ExampleStruct3 structure to be created, modified and sent between nodes. Variables hold no inherent meaning. */
typedef struct {
	float playerHealth;
	float playerMana;
	int playerNameSize;
	int itemListSize;
	char playerName[100];
	char itemList[50];
	double werewolfPercentage;
} ExampleStruct3;

/*
 * Function to construct a complex datatype (ExampleStruct1) which can be sent out to another node by MPI
 *
 * @return: Returns empty MPI object representing the struct ExampleStruct1 that can be filled and sent to other nodes
 */
MPI::Datatype createExampleStruct1() {
	const int count = 4;		//int variable to denote number of data types to be created
	MPI::Datatype typesInStruct[count] = {MPI::FLOAT, MPI::INT, MPI::CHAR, MPI::DOUBLE};	//Array of MPI variations/wrapped variables to be constructed
	int arrayBlockLengths [count] = {15, 3, 1, 1};			//Array of number of instances of matching types in a row in memory
	MPI::Aint objAddress, address1, address2, address3, address4;	//Initialising memory address variables for data types
	MPI::Aint arrayDisplacements[count];				//Array for the created variables
	ExampleStruct1 sbuf;						//instance of struct to be measured for addresses
	objAddress = MPI::Get_address(&sbuf);				//Get addresses based on struct
	address1 = MPI::Get_address(&sbuf.list);
	address2 = MPI::Get_address(&sbuf.size);
	address3 = MPI::Get_address(&sbuf.letter);
	address4 = MPI::Get_address(&sbuf.number);
	arrayDisplacements[0] = address1 - objAddress;			//Save displaced actual addresses in array
	arrayDisplacements[1] = address2 - objAddress;
	arrayDisplacements[2] = address3 - objAddress;
	arrayDisplacements[3] = address4 - objAddress;
	MPI::Datatype exampleStruct1;					//Instantiate struct
	exampleStruct1 = MPI::Datatype::Create_struct(count, arrayBlockLengths, arrayDisplacements, typesInStruct);	//Create structure with necessary variables
	exampleStruct1.Commit();
	return exampleStruct1;	
}

/* Same as createExampleStruct1 */
MPI::Datatype createExampleStruct2() {
	const int count = 3;
	MPI::Datatype typesInStruct[count] = {MPI::INT, MPI::CHAR, MPI::LONG_DOUBLE};
	int arrayBlockLengths [count] = {34, 50, 1};
	MPI::Aint objAddress2, address12, address22, address32;
	MPI::Aint arrayDisplacements[count];
	ExampleStruct2 sbuf;
	objAddress2 = MPI::Get_address(&sbuf);
	address12 = MPI::Get_address(&sbuf.playerlist);
	address22 = MPI::Get_address(&sbuf.levelName);
	address32 = MPI::Get_address(&sbuf.randVar);
	arrayDisplacements[0] = address12 - objAddress2;
	arrayDisplacements[1] = address22 - objAddress2;
	arrayDisplacements[2] = address32 - objAddress2;
	MPI::Datatype exampleStruct2;
	exampleStruct2 = MPI::Datatype::Create_struct(count, arrayBlockLengths, arrayDisplacements, typesInStruct);
	exampleStruct2.Commit();
	return exampleStruct2;	
}

/* Same as createExampleStruct1 */
MPI::Datatype createExampleStruct3() {
	const int count = 4;
	MPI::Datatype typesInStruct[count] = {MPI::FLOAT, MPI::INT, MPI::CHAR, MPI::DOUBLE};
	int arrayBlockLengths [count] = {2, 2, 150, 1};
	MPI::Aint objAddress3, address13, address23, address33, address43;
	MPI::Aint arrayDisplacements[count];
	ExampleStruct3 sbuf;
	objAddress3 = MPI::Get_address(&sbuf);
	address13 = MPI::Get_address(&sbuf.playerHealth);
	address23 = MPI::Get_address(&sbuf.playerNameSize);
	address33 = MPI::Get_address(&sbuf.playerName);
	address43 = MPI::Get_address(&sbuf.werewolfPercentage);
	arrayDisplacements[0] = address13 - objAddress3;
	arrayDisplacements[1] = address23 - objAddress3;
	arrayDisplacements[2] = address33 - objAddress3;
	arrayDisplacements[3] = address43 - objAddress3;
	MPI::Datatype exampleStruct3;
	exampleStruct3 = MPI::Datatype::Create_struct(count, arrayBlockLengths, arrayDisplacements, typesInStruct);
	exampleStruct3.Commit();
	return exampleStruct3;	
}

/* Function to print out all structure data.
 *
 * @Params: local instances of example structs 1-3 with data added to them
 */
void displayStructValues(ExampleStruct1 local_exampleStruct1, ExampleStruct2 local_exampleStruct2, ExampleStruct3 local_exampleStruct3) {
	std::cout << "ExampleStruct1:" << std::endl;
	std::cout << "> list: ";
	for (int i = 0; i < local_exampleStruct1.size; i++) {		//Iterates over array as C style arrays cannot be directly accessed for modification
		std::cout << local_exampleStruct1.list[i] << " ";
	}
	std::cout << '\n' << "> size: " << local_exampleStruct1.size << std::endl;
	std::cout << "> x: " << local_exampleStruct1.x << std::endl;
	std::cout << "> y: " << local_exampleStruct1.y << std::endl;
	std::cout << "> letter: " << local_exampleStruct1.letter << std::endl;
	std::cout.precision(12);
	std::cout << "> number: " << local_exampleStruct1.number << std::endl;

	std::cout << "" << std::endl;

	std::cout << "ExampleStruct2:" << std::endl;
	std::cout << "> playerlist: ";
	for (int i = 0; i < local_exampleStruct2.playerlistSize; i++) {
		std::cout << local_exampleStruct2.playerlist[i] << " ";
	}
	std::cout << '\n' << "> playerlistSize: " << local_exampleStruct2.playerlistSize << std::endl;
	std::cout << "> levelName: " << local_exampleStruct2.levelName << std::endl;
	std::cout << "> levelNameSize: " << local_exampleStruct2.levelNameSize << std::endl;
	std::cout << "> gameBoardWidth: " << local_exampleStruct2.gameBoardWidth << std::endl;
	std::cout << "> gameBoardHeight: " << local_exampleStruct2.gameBoardHeight << std::endl;
	std::cout << "> randVar: " << local_exampleStruct2.randVar << std::endl;

	std::cout << "" << std::endl;

	std::cout << "ExampleStruct3:" << std::endl;
	std::cout << "> playerHealth: " << local_exampleStruct3.playerHealth << std::endl;
	std::cout << "> playerMana: " << local_exampleStruct3.playerMana << std::endl;
	std::cout << "> playerName: " << local_exampleStruct3.playerName << std::endl;
	std::cout << "> playerNameSize: " << local_exampleStruct3.playerNameSize << std::endl;
	std::cout << "> itemList: " << local_exampleStruct3.itemList << std::endl;
	std::cout << "> itemListSize: " << local_exampleStruct3.itemListSize << std::endl;
	std::cout << "> werewolfPercentage: " << local_exampleStruct3.werewolfPercentage << std::endl;
}

int main(int argc, char** argv) {
	MPI_Init(NULL,NULL);
	int comm_size, world_rank, namelen;
	char node_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Get_processor_name(node_name, &namelen);
	MPI::Datatype exampleStruct1 = createExampleStruct1();
	MPI::Datatype exampleStruct2 = createExampleStruct2();
	MPI::Datatype exampleStruct3 = createExampleStruct3();

	ExampleStruct1 local_exampleStruct1;	//Create local empty structures on each node
	ExampleStruct2 local_exampleStruct2;
	ExampleStruct3 local_exampleStruct3;

	int source = 0;			//head node
	int destination = 5;		//node to send and recieve data from

	if (world_rank == source) {	//Check if currently on head node
		local_exampleStruct1.size = 15;				//Fill local empty structures up with demo random data
		for (int i = 0; i < local_exampleStruct1.size; i++) {
			float n = i;
			local_exampleStruct1.list[i] = n / 2;
		}
		local_exampleStruct1.x = 10;
		local_exampleStruct1.y = -15;
		local_exampleStruct1.letter = 'z';
		local_exampleStruct1.number = 3.14159265359;

		local_exampleStruct2.playerlistSize = 30;
		for (int i = 0; i < local_exampleStruct2.playerlistSize; i++) {
			local_exampleStruct2.playerlist[i] = i;
		}
		local_exampleStruct2.gameBoardWidth = 25;
		local_exampleStruct2.gameBoardHeight = 25;
		local_exampleStruct2.levelNameSize = 6;
		strcpy(local_exampleStruct2.levelName, "Forest");
		local_exampleStruct2.randVar = 0.1234567890123;

		local_exampleStruct3.playerHealth = 100.0;
		local_exampleStruct3.playerMana = 100.0;
		strcpy(local_exampleStruct3.playerName, "Hunter");
		local_exampleStruct3.playerNameSize = 6;
		strcpy(local_exampleStruct3.itemList, "Silver bullet");
		local_exampleStruct3.itemListSize = 13;
		local_exampleStruct3.werewolfPercentage = 25.4567;

		MPI_Send(&local_exampleStruct1,1, exampleStruct1, destination, 0, MPI_COMM_WORLD);	//Send all all structures to destination node 
		MPI_Send(&local_exampleStruct2,1, exampleStruct2, destination, 0, MPI_COMM_WORLD); 
		MPI_Send(&local_exampleStruct3,1, exampleStruct3, destination, 0, MPI_COMM_WORLD); 
	}

	if (world_rank == destination) {	//Check if currently on destination node
		MPI_Recv(&local_exampleStruct1, 1, exampleStruct1, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);	//Recieve data from head node, filling up local empty structures
		MPI_Recv(&local_exampleStruct2, 1, exampleStruct2, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&local_exampleStruct3, 1, exampleStruct3, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		std::cout << '\n' << "> structures received by " << node_name << '\n' << std::endl;

		displayStructValues(local_exampleStruct1, local_exampleStruct2, local_exampleStruct3);		//Print out recieved structure data

		local_exampleStruct1.size = 13;				//Change data values to be sent back to head node
		for (int i = 0; i < local_exampleStruct1.size; i++) {
			float n = i;
			local_exampleStruct1.list[i] = (n + 100) / 2;
		}
		local_exampleStruct1.x = 5;
		local_exampleStruct1.y = 26;
		local_exampleStruct1.letter = 'a';
		local_exampleStruct1.number = 2.71828183;

		local_exampleStruct2.playerlistSize = 25;
		for (int i = 0; i < local_exampleStruct2.playerlistSize; i++) {
			local_exampleStruct2.playerlist[i] = i + 5;
		}
		local_exampleStruct2.gameBoardWidth = 30;
		local_exampleStruct2.gameBoardHeight = 30;
		local_exampleStruct2.levelNameSize = 15;
		strcpy(local_exampleStruct2.levelName, "Abandoned house");
		local_exampleStruct2.randVar = -0.0987654321234;

		local_exampleStruct3.playerHealth = 75.59;
		local_exampleStruct3.playerMana = 26.50;
		strcpy(local_exampleStruct3.playerName, "Werewolf");
		local_exampleStruct3.playerNameSize = 8;
		strcpy(local_exampleStruct3.itemList, "claw");
		local_exampleStruct3.itemListSize = 4;
		local_exampleStruct3.werewolfPercentage = 99.9999;

		MPI_Send(&local_exampleStruct1, 1, exampleStruct1, source, 0, MPI_COMM_WORLD);		//Send struct data back to head node
		MPI_Send(&local_exampleStruct2, 1, exampleStruct2, source, 0, MPI_COMM_WORLD);
		MPI_Send(&local_exampleStruct3, 1, exampleStruct3, source, 0, MPI_COMM_WORLD);
	}

	if (world_rank == source) {
		sleep(1);	//Sleep to print things out in order
		std::cout << '\n' << "> original structures created by " << node_name << '\n' << std::endl;
		displayStructValues(local_exampleStruct1, local_exampleStruct2, local_exampleStruct3);		//Display original data created on host node

		MPI_Recv(&local_exampleStruct1, 1, exampleStruct1, destination, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);		//Get data from destination node and replace current data with new data
		MPI_Recv(&local_exampleStruct2, 1, exampleStruct2, destination, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&local_exampleStruct3, 1, exampleStruct3, destination, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		std::cout << '\n' << "> altered structures received by " << node_name << '\n' << std::endl;
		displayStructValues(local_exampleStruct1, local_exampleStruct2, local_exampleStruct3);		//Display data sent by destination node
	}


	MPI_Finalize();
	return 0;
}

