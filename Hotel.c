#pragma warning (disable:4996)
#include "Hotel.h"
#include "Room.h"
#include "Customer.h"
#include "Reservation.h"

void checkIn(hotel_t* theHotel, customer_t*** customerArray, int* sizeOfCustomersArray, reservation_t*** reservationArray, int* sizeOfReservationArray) {

	printf("For check in to exist customer, please enter his/her ID \n");
	printCustomerArray(customerArray, sizeOfCustomersArray);
	printf("For Check in to new customer, press 0 \n");

	int choose;

	customer_t* tempCustomer = NULL;

	do //check if get correct num to do check in. 0-sizeCustomersArray.
	{
		scanf("%d", &choose);

		if (choose < 0 || choose > *sizeOfCustomersArray) {
			printf("Sorry. wrong number.\n | please enter number between %d to %d\n", 0, *sizeOfCustomersArray);
		}
		else {
			if (choose == 0)
			{
				//add New Customer And Do Reservation
				addCustomer(customerArray, tempCustomer, sizeOfCustomersArray);
				tempCustomer = (*customerArray)[(*sizeOfCustomersArray) - 1];

			}
			else
			{
				tempCustomer = (*customerArray)[(*sizeOfCustomersArray) - 1];
			}
		}

	} while (choose > *sizeOfCustomersArray || choose < 0);

	//now i have a pointer for customer to add to the reservation.

	reservation_t* newReservation = NULL;
	newReservation = (reservation_t*)calloc(1, sizeof(reservation_t)); // for one reservaiton.

	if (!newReservation)//--> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return;
	}

	int numOfRoom = 0;
	room_t* freeRoomForReservation = getPtrToFreeRoom(theHotel, &numOfRoom);


	initialReservation(&newReservation, freeRoomForReservation, tempCustomer);

	addReservation(reservationArray, sizeOfReservationArray, newReservation); // add newReservation to the reservation array.
	printf("Hey welcome to the Hotel California \n Your room number is | %d | \n Enjoy \n", numOfRoom);


}

/*Helper method for print all taken room to show in the program*/

void printAllTakenRooms(hotel_t* theHotel)
{
	int i, j;

	for (i = 0; i < theHotel->numOfFloors; i++)
	{
		for (j = 0; j < theHotel->numOfRoomPerFloor; j++)
		{
			if (theHotel->roomsMatrix[i][j].availableRoom == 0)
			{
				printf("Room number | %d | is taken \n", (i + 1)*MAX_NUM_OF_ROOMS_PER_FLOOR + j);
			}
		}
	}
}


room_t* getPtrToFreeRoom(hotel_t* theHotel, int* numOfTheRoom)

{
	int i, j;

	for (i = 0; i < theHotel->numOfFloors; i++)
	{
		for (j = 0; j < theHotel->numOfRoomPerFloor; j++)
		{
			if (theHotel->roomsMatrix[i][j].availableRoom == 1)
			{
				*numOfTheRoom = ((i + 1))*MAX_NUM_OF_ROOMS_PER_FLOOR + j;
				return &(theHotel->roomsMatrix[i][j]);
			}
		}
	}
	return NULL; //if all the rooms are taken 
}

void initialHotel(hotel_t* theHotel)
{

	int numOfFloors, numOfRoomsPerFloor;
	int legal = 0;
	do
	{
		printf("Hey,please insert num of floor %d-%d\n", MIN_NUM_OF_FLOORS, MAX_NUM_OF_FLOORS);
		scanf("%d", &numOfFloors);
		if (numOfFloors < MIN_NUM_OF_FLOORS || numOfFloors > MAX_NUM_OF_FLOORS)
		{
			printf("I ask for %d-%d\n", MIN_NUM_OF_FLOORS, MAX_NUM_OF_FLOORS);
		}
		else
		{
			legal = 1;
		}

	} while (legal != 1);

	legal = 0;
	do
	{
		printf("Hey,please insert num of rooms per floor %d-%d\n", MIN_NUM_OF_FLOORS, MAX_NUM_OF_ROOMS_PER_FLOOR);
		scanf("%d", &numOfRoomsPerFloor);
		if (numOfRoomsPerFloor < MIN_NUM_OF_ROOMS_PER_FLOOR
			|| numOfRoomsPerFloor > MAX_NUM_OF_ROOMS_PER_FLOOR)
		{
			printf("I ask for %d-%d...\n", MIN_NUM_OF_FLOORS, MAX_NUM_OF_ROOMS_PER_FLOOR);
		}
		else
		{
			legal = 1;
		}
	} while (legal != 1);

	theHotel->numOfFloors = numOfFloors;
	theHotel->numOfRoomPerFloor = numOfRoomsPerFloor;

	theHotel->roomsMatrix = (room_t**)malloc(theHotel->numOfFloors * sizeof(room_t*));
	if (!theHotel->roomsMatrix)//--> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return;
	}

	int i, j;
	for (i = 0; i < numOfFloors; i++)
	{
		//initial every floor with the number of rooms
		theHotel->roomsMatrix[i] = (room_t*)malloc(theHotel->numOfRoomPerFloor * sizeof(room_t));
		if (!theHotel->roomsMatrix[i])//--> allocaton didn't succeed
		{
			printf("ERROR! Out of memory!\n");
			return;
		}
	}

	//initial every room for the hotel
	for (i = 0; i < numOfFloors; i++)
	{
		for (j = 0; j < numOfRoomsPerFloor; j++)
		{
			initialRoom(&(theHotel->roomsMatrix[i][j]));
		}
	}
}


void showHotelStatus(hotel_t* theHotel)
{
	int i, j;
	for (i = 0; i < theHotel->numOfFloors; i++)
	{
		for (j = 0; j < theHotel->numOfRoomPerFloor; j++)
		{
			printRoom(&(theHotel->roomsMatrix[i][j]));
		}
	}

}

void printSpecificRoom(hotel_t* theHotel, int roomNumber) {
	int floor = (roomNumber / 100) - 1; // 3 digits room number. /100 give me the units. and minus 1 because we start from floor 0..
	//and the roomsnumber in floor 0 is 100-199...
	int roomNumberInFloor = roomNumber % 100;

	// *100 cause every room is 3 digits.

	if (roomNumber > ((MAX_NUM_OF_ROOMS_PER_FLOOR * theHotel->numOfFloors) + (theHotel->numOfRoomPerFloor)) //biggest room number.
		|| roomNumber < MAX_NUM_OF_ROOMS_PER_FLOOR) //100 is the minimal room
	{
		printf("\nSorry. this room isnt exist in this Hotel.\n");
	}
	else
	{
		printf("\nFLOOR IS : %d:\n", floor);
		printf("\nRoom in floor: %d: \n", roomNumberInFloor);

		printf("\nROOM SPECFIC IS: \n");
		printRoom(&(theHotel->roomsMatrix[floor][roomNumberInFloor]));
	}
}

void freeRoomsMemory(hotel_t* theHotel)
{
	int i;
	for (i = 0; i < theHotel->numOfFloors; i++)
	{
		free(theHotel->roomsMatrix[i]); //free floor by floor
	}
	free(theHotel->roomsMatrix);
}
