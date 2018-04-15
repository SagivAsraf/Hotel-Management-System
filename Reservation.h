#ifndef __RESERVATION_H
#define __RESERVATION_H

#include <stdlib.h>

#include "Customer.h"
#include "Room.h"

#define MAX_PEOPLE_IN_ROOM_AND_BREAKFAST 4
#define MIN_PEOPLE_IN_ROOM 1
#define MIN_PEOPLE_IN_BREAKFAST 0

typedef struct Reservation
{
	customer_t* customerPtr;
	int numOfPeopleSleepInRoom; //1-4!
	int numOfPeopleEatBreakfast;
	room_t* roomPtr;
	int checkOut; //0 not check out 1 yes check out

}reservation_t;

void addReservation(reservation_t*** reservationArray, int* sizeOfReservationArray, reservation_t* reservationToAdd);

void initialReservation(reservation_t** newReservation, room_t* freeRoomPtr, customer_t* customerOfReservation);

void setNumOfPeopleInRoomAndEatBreakFast(reservation_t** newReservation);
	
void freeReservations(reservation_t*** reservationsArrayToFree, int* sizeOfReservationArray);

#endif
