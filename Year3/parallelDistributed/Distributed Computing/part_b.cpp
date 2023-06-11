#include <iostream>
#include <string>    
#include <cstring>
#include "mpi.h"


/* ExampleStruct1 structure to be created, modified and sent between nodes. Variables hold no inherent meaning. */
typedef struct {
	float list[15];
	int size;
	int x;
	int y;
	char letter;
	double number;
}ExampleStruct1;

/* ExampleStruct2 structure to be created, modified and sent between nodes. Variables hold no inherent meaning. */
typedef struct {
	int playerlist[30];
	int playerlistSize;
	int levelNameSize;
	int gameBoardWidth;
	int gameBoardHeight;
	char levelName[50];
	long double randVar;
}ExampleStruct2;

/* ExampleStruct3 structure to be created, modified and sent between nodes. Variables hold no inherent meaning. */
typedef struct {
	float playerHealth;
	float playerMana;
	int playerNameSize;
	int itemListSize;
	char playerName[100];
	char itemList[50];
	double werewolfPercentage;
}ExampleStruct3;

/*
 * Function to construct a complex datatype (ExampleStruct1) which can be sent out to another node by MPI
 * 
 * @return: Returns empty MPI object representing the struct ExampleStruct1 that can be filled and sent to other nodes
 * */
MPI::Datatype createExampleStruct1() {
	const int count = 4;			//int variable to denote number of data types to be created
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



int main(int argc, char** argv) {
	MPI_Init(NULL,NULL);
	int comm_size, world_rank, namelen;
	char node_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);			//Get comm size of each node
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);			//Get comm rank of each node
	MPI_Get_processor_name(node_name, &namelen);			//Get processor name of each node
	MPI::Datatype exampleStruct1 = createExampleStruct1();		
	MPI::Datatype exampleStruct2 = createExampleStruct2();
	MPI::Datatype exampleStruct3 = createExampleStruct3();

	int source = 0;			//Head node
	int destination = 5;		//Node that the head node will communicate with

	if (world_rank == source){	//Check if head node
		ExampleStruct1 local_exampleStruct1;	//Instantiate structures local to only the head node
		ExampleStruct2 local_exampleStruct2;
		ExampleStruct3 local_exampleStruct3;
		
		local_exampleStruct1.size = 15;		//Set size of array of floats
		for (int i = 0; i < local_exampleStruct1.size; i++) {	//Loop over array to give it values as C style arrays cannot be directly accessed
			float n = i;
			local_exampleStruct1.list[i] = n / 2;		//Add unimportant float values to array
		}
		//Fill all structs with random demo values
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
		
		MPI_Send(&local_exampleStruct1,1, exampleStruct1, destination, 0, MPI_COMM_WORLD);	//Send all three structs to destination node
		MPI_Send(&local_exampleStruct2,1, exampleStruct2, destination, 0, MPI_COMM_WORLD); 
		MPI_Send(&local_exampleStruct3,1, exampleStruct3, destination, 0, MPI_COMM_WORLD); 
	}

	if (world_rank == destination){
		ExampleStruct1 local_exampleStruct12;	//Create empty local instances of structs
		ExampleStruct2 local_exampleStruct22;
		ExampleStruct3 local_exampleStruct32;

		MPI_Recv(&local_exampleStruct12, 1, exampleStruct1, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);	//Recieve data sent by the head node, setting the data into local empty structs
		MPI_Recv(&local_exampleStruct22, 1, exampleStruct2, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&local_exampleStruct32, 1, exampleStruct3, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		std::cout << "> host structures Received by " << node_name << '\n' << std::endl;	//Print out all of the recieved data

		std::cout << "ExampleStruct1:" << std::endl;
		std::cout << "> list: ";
		for (int i = 0; i < local_exampleStruct12.size; i++) {
			std::cout << local_exampleStruct12.list[i] << " ";
		}
		std::cout << '\n' << "> size: " << local_exampleStruct12.size << std::endl;
		std::cout << "> x: " << local_exampleStruct12.x << std::endl;
		std::cout << "> y: " << local_exampleStruct12.y << std::endl;
		std::cout << "> letter: " << local_exampleStruct12.letter << std::endl;
		std::cout.precision(12);
		std::cout << "> number: " << local_exampleStruct12.number << std::endl;
		
		std::cout << "" << std::endl;

		std::cout << "ExampleStruct2:" << std::endl;
		std::cout << "> playerlist: ";
		for (int i = 0; i < local_exampleStruct22.playerlistSize; i++) {
			std::cout << local_exampleStruct22.playerlist[i] << " ";
		}
		std::cout << '\n' << "> playerlistSize: " << local_exampleStruct22.playerlistSize << std::endl;
		std::cout << "> levelName: " << local_exampleStruct22.levelName << std::endl;
		std::cout << "> levelNameSize: " << local_exampleStruct22.levelNameSize << std::endl;
		std::cout << "> gameBoardWidth: " << local_exampleStruct22.gameBoardWidth << std::endl;
		std::cout << "> gameBoardHeight: " << local_exampleStruct22.gameBoardHeight << std::endl;
		std::cout << "> randVar: " << local_exampleStruct22.randVar << std::endl;

		std::cout << "" << std::endl;
	
		std::cout << "ExampleStruct3:" << std::endl;
		std::cout << "> playerHealth: " << local_exampleStruct32.playerHealth << std::endl;
		std::cout << "> playerMana: " << local_exampleStruct32.playerMana << std::endl;
		std::cout << "> playerName: " << local_exampleStruct32.playerName << std::endl;
		std::cout << "> playerNameSize: " << local_exampleStruct32.playerNameSize << std::endl;
		std::cout << "> itemList: " << local_exampleStruct32.itemList << std::endl;
		std::cout << "> itemListSize: " << local_exampleStruct32.itemListSize << std::endl;
		std::cout << "> werewolfPercentage: " << local_exampleStruct32.werewolfPercentage << std::endl;
	}

	MPI_Finalize();
	return 0;
}

