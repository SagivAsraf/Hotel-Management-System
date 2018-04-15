#pragma warning (disable:4996)
#include <stdio.h>

#include "Hotel.h"
#include "Room.h"
#include "Customer.h"
#include "Reservation.h"

void printMenu();

void main()
{

	int choose;

	//Set new hotel,rooms,customers...

	hotel_t californiaHotel;

	customer_t* tempCustomer = NULL;
	customer_t** customersArray = NULL;
	int sizeOfCustomerArray = 0;

	reservation_t* tempReservation = NULL;
	reservation_t** reservationArray = NULL;
	int sizeOfreservationArray = 0;


	//initial hotel
	initialHotel(&californiaHotel);

	printf("Welcome to the hotel California\n");

	do
	{

		printMenu();

		scanf("%d", &choose);
		switch (choose)
		{

		case 1:
		{
			printf("Hey, you chose to show the hotel details\n");
			showHotelStatus(&californiaHotel);
			break;
		}
		case 2:
		{
			printf("Hey, you chose to add customer\n");
			addCustomer(&customersArray, tempCustomer, &sizeOfCustomerArray); 
			//we ask Keren for send an adrress of customer,she said its fine
			break;

		}
		case 3:
		{
			printf("Hey, you chose to check in\n");
			int numOfRoom = 0; //fictitious varriable
			if (getPtrToFreeRoom(&californiaHotel, &numOfRoom) == NULL)
			{
				printf("Sorry all the rooms are taken go back tomorrow\n");
			}
			else {
				checkIn(&californiaHotel, &customersArray,
					&sizeOfCustomerArray, &reservationArray, &sizeOfreservationArray);
			}
			break;
		}
		case 4:
		{
			printf("Hey, you chose to check out\n");
			int roomNumberToCheckOut = 0;
			int firstRoomTaken = 1000; //in purpose.cause i want here the first(minimal) number of room that will be taken.
			int lastRoomTaken = 100;
			int legalCheckOut = 0;

			printAllTakenRooms(&californiaHotel); //print all the taken rooms

			printf("please choose a nubmber from the list: ");
			scanf("%d", &roomNumberToCheckOut);

			//Here i know for sure i have correct number of room to do check out
			int floorNumber = (roomNumberToCheckOut / 100) - 1;
			//Cause room number 202, is in 1 floor... so 202/100 is 2, and 2-1 = 1 - exactly what I wanted.
			int roomNumberInFloor = roomNumberToCheckOut % 100; // give the units and the "asarot"; 

			/*I will pass on my reservation array, and search for the address of
			the room that i know his address. when i got equals addresses so -FOUND.*/
			int i;
			for (i = 0; i < sizeOfreservationArray; i++)
			{
				if ((reservationArray[i]->roomPtr) ==
					(&(californiaHotel.roomsMatrix[floorNumber][roomNumberInFloor])))
				{
					if (reservationArray[i]->checkOut == 1)
					{   //for option that you already did check out,and than you try to do again to the same room.
						printf("This room isnt invited. No check out \n");
					}
					else
					{
						legalCheckOut = 1;
						//I got to the correct reservation. and now im doing check out.
						reservationArray[i]->checkOut = 1; // Yes check out
						//initial the room we want to check out from.
						initialRoom(&(californiaHotel.roomsMatrix[floorNumber][roomNumberInFloor]));
					}
				}
			}
			if (legalCheckOut == 0)
			{
				printf("Sorry. we cant do check out for this room. I asked you to choose a number from the list. \n");
			}
			break;
		}

		case 5:
		{
			printf("Hey, you chose print specific room details\n");
			int roomNumber = 0;
			printf("Plase insert room number from %d to %d \n", FIRST_ROOM_NUMBER, LAST_ROOM_NUMBER);
			scanf("%d", &roomNumber);
			printSpecificRoom(&californiaHotel, roomNumber);

			break;

		}
		case 6:
		{
			printf("Hey,you chose 6\n");
			printf("I will update all your customers to begin with capital letter! \n");
			printf("And I will print it for you to see the changes \n");

			updtateCustomersToCapital(&customersArray, &sizeOfCustomerArray);
			printCustomerArray(&customersArray, &sizeOfCustomerArray);
			break;
		}


		case 7:
		{
			customer_t** cusArrOfSubStrings = NULL; //for case 7
			int sizeOfSubStringNamesArray = 0;

			char subStringToSearchFor[MAX_LENGTH_CUSTOMER_NAME];
			printf("Hey,you chose 7 \n");
			printf("I will give you back a new array wich contain all the customers that have a sub string as you want. \n\n");
			printf("Please enter a SubString you want to check : \n");

			scanf("%s", subStringToSearchFor);

			cusArrOfSubStrings = custmersNameSubString(customersArray, &sizeOfSubStringNamesArray,
				&sizeOfCustomerArray, subStringToSearchFor);

			if (sizeOfSubStringNamesArray != 0)
			{
				printCustomerArray(&cusArrOfSubStrings, &sizeOfSubStringNamesArray);
			}
			else
			{
				printf("No name is sub string... \n");
			}

			break;
		}
		case 0:
		{
			printf("You choose to exit! GB \n");
			//Free memory . out of program

			//free customers
			freeCustomers(&customersArray, &sizeOfCustomerArray);

			//free rooms of the hotel
			freeRoomsMemory(&californiaHotel);

			//free resvertations
			freeReservations(&reservationArray, &sizeOfreservationArray);

			break;
		}

		default: printf("Wrong choice");
			break;
		}

	} while (choose != 0);

	system("pause");
}


/*Helper method to print the menu*/
void printMenu()
{
	printf("Choose one of the next options: \n");
	printf("	1 --> To print hotel state\n");
	printf("	2 --> To add customer\n");
	printf("	3 --> To check in\n");
	printf("	4 --> To check out\n");
	printf("	5 --> To print specific room details\n");
	printf("	6 --> To change all the customers first letter in the name to capital letter\n");
	printf("	7 --> To get an array of all the customers that their name contain sub string you choose\n");
	printf("    0 --> To Exit\n");
}
