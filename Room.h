#ifndef __ROOM_H
#define __ROOM_H


#include <stdio.h>
#include <stdlib.h>
#define FIRST_ROOM_NUMBER 100
#define LAST_ROOM_NUMBER 999

typedef struct
{
	int availableRoom; //0 not available 1 yes
	int numOfPeopleInTheRoom;
	int numOfPeopleBreakfast;

} room_t;

void initialRoom(room_t* room);
void printRoom(room_t* room);
void setNumOfRoomToCheckOut(int* firstRoomTaken, int* lastRoomTaken, int* roomNumberToCheckOut);

#endif
