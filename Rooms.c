#pragma warning (disable:4996)


#include "Room.h"

void initialRoom(room_t* room) {

	room->availableRoom = 1;
	room->numOfPeopleBreakfast = 0;
	room->numOfPeopleInTheRoom = 0;
}

void printRoom(room_t* room) {
	if (room->availableRoom == 0) {
		printf("The room is not available\n");
		printf("\nThe number of the people in room is : %d \n", room->numOfPeopleInTheRoom);
		printf("\nThe number of the people in that eat breakfast : %d \n", room->numOfPeopleBreakfast);
	}
	else {
		printf("The room is available\n");
	}

}
/*Helper method for cleaner main and to set the num of room to check out, with check of the input*/
void setNumOfRoomToCheckOut(int* firstRoomTaken, int* lastRoomTaken, int* roomNumberToCheckOut) {

	if (*firstRoomTaken == -1 || *lastRoomTaken == -1)
	{	// all the rooms are available. no check out!
		printf("Our hotel is E-M-P-T-Y. no rooms to do check out \n");
		printf("To check in, press 3 ;) \n");
	}
	else {
		printf("Please choose room number from the list just between: %d-%d\n", *firstRoomTaken, *lastRoomTaken);
		do
		{
			scanf("%d", roomNumberToCheckOut);
			if (*roomNumberToCheckOut > *lastRoomTaken || *roomNumberToCheckOut < *firstRoomTaken) {
				printf("wrong number. please choose number between: %d-%d\n", *firstRoomTaken, *lastRoomTaken);
			}
		} while (*roomNumberToCheckOut > *lastRoomTaken || *roomNumberToCheckOut < *firstRoomTaken);
		//here i know that i got a room number that is in the list of the taken rooms.
	}

}
