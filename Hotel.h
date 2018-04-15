#ifndef __HOTEL_H
#define __HOTEL_H

#include <stdlib.h>

#include "Room.h"
#include "Customer.h"
#include "Reservation.h"
#define MAX_NUM_OF_FLOORS 9
#define MIN_NUM_OF_ROOMS_PER_FLOOR 1
#define MIN_NUM_OF_FLOORS 1
#define MAX_NUM_OF_ROOMS_PER_FLOOR 100



typedef struct Hotel
{
	int numOfFloors;
	int numOfRoomPerFloor; //max - 100 , all the floors same num rooms
	room_t** roomsMatrix;

}hotel_t;


void initialHotel(hotel_t* theHotel);
void showHotelStatus(hotel_t* theHotel);
void printSpecificRoom(hotel_t* theHotel, int roomNumber);
void checkIn(hotel_t* theHotel, customer_t*** customerArray, 
	int* sizeOfCustomersArray, reservation_t*** reservationArray, int* sizeOfReservationArray);
void printAllTakenRooms(hotel_t* theHotel);
room_t* getPtrToFreeRoom(hotel_t* theHotel, int* numOfTheRoom);

void freeRoomsMemory(hotel_t* theHotel);

#endif
