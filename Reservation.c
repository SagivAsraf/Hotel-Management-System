#pragma warning (disable:4996)
#include "Hotel.h"
#include "Room.h"
#include "Customer.h"
#include "Reservation.h"


void addReservation(reservation_t*** reservationArray, int* sizeOfReservationArray, reservation_t* reservationToAdd) {

	(*sizeOfReservationArray)++;

	(*reservationArray) = (reservation_t**)realloc(*reservationArray, (*sizeOfReservationArray) * sizeof(reservation_t*));
	if (!*reservationArray)//--> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return;
	}
	(*reservationArray)[(*sizeOfReservationArray) - 1] = reservationToAdd;
}


void initialReservation(reservation_t** newReservation, room_t* freeRoomPtr, customer_t* customerOfReservation) {


	*newReservation = (reservation_t*)calloc(1, sizeof(reservation_t));
	(*newReservation)->checkOut = 0; // check in and not check out :)
	(*newReservation)->customerPtr = customerOfReservation;
	setNumOfPeopleInRoomAndEatBreakFast(newReservation);
	freeRoomPtr->numOfPeopleBreakfast = (*newReservation)->numOfPeopleEatBreakfast;
	freeRoomPtr->numOfPeopleInTheRoom = (*newReservation)->numOfPeopleSleepInRoom;
	freeRoomPtr->availableRoom = 0; //now isnt available.
	(*newReservation)->roomPtr = freeRoomPtr;

}

void setNumOfPeopleInRoomAndEatBreakFast(reservation_t** newReservation) {

	int numOfPeopleInRoom = 0;
	int numOfPeopleEatBreakfast = 0;
	//now in do while i did it a little bit different, without legal.
	do
	{
		printf("Hey, please enter num of people that in the room %d-%d \n", MIN_PEOPLE_IN_ROOM, MAX_PEOPLE_IN_ROOM_AND_BREAKFAST);
		scanf("%d", &numOfPeopleInRoom);
		if (numOfPeopleInRoom<MIN_PEOPLE_IN_ROOM || numOfPeopleInRoom>MAX_PEOPLE_IN_ROOM_AND_BREAKFAST) {
			printf("I ask  %d-%d try again \n", MIN_PEOPLE_IN_ROOM, MAX_PEOPLE_IN_ROOM_AND_BREAKFAST);
		}
		else {
			(*newReservation)->numOfPeopleSleepInRoom = numOfPeopleInRoom;
		}
	} while (numOfPeopleInRoom<MIN_PEOPLE_IN_ROOM || numOfPeopleInRoom>MAX_PEOPLE_IN_ROOM_AND_BREAKFAST);

	do
	{
		printf("Hey, please enter num of people that eat breakfast in the room %d-%d \n", MIN_PEOPLE_IN_BREAKFAST, MAX_PEOPLE_IN_ROOM_AND_BREAKFAST);
		scanf("%d", &numOfPeopleEatBreakfast);
		if (numOfPeopleEatBreakfast < MIN_PEOPLE_IN_BREAKFAST || numOfPeopleEatBreakfast > MAX_PEOPLE_IN_ROOM_AND_BREAKFAST) {
			printf("I ask  %d-%d try again", MIN_PEOPLE_IN_BREAKFAST, MAX_PEOPLE_IN_ROOM_AND_BREAKFAST);
		}
		else {
			(*newReservation)->numOfPeopleEatBreakfast = numOfPeopleEatBreakfast;
		}
	} while (numOfPeopleEatBreakfast< MIN_PEOPLE_IN_BREAKFAST || numOfPeopleEatBreakfast > MAX_PEOPLE_IN_ROOM_AND_BREAKFAST);
}

void freeReservations(reservation_t*** reservationsArrayToFree, int* sizeOfReservationArray)
{
	int i;
	for (i = 0; i < *sizeOfReservationArray; i++) {
		free((*reservationsArrayToFree)[i]);
	}
}
