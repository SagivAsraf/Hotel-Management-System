#ifndef __CUSTOMER_H
#define __CUSTOMER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LENGTH_CUSTOMER_NAME 100 /*we ask Andrey, this is the best way for 
get a string (that we dont know the size) from the user, and after this we 
doing malloc as the size the user gave us.*/
#define MAX_INPUT_CREDIT_CARD_LENGTH 24

#define CREDIT_CARD_LENGTH 12
#define MAX_YEAR_CARD 2020
#define MIN_YEAR_CARD 2010
#define DIFFERENCE_BETWEEN_A_TO_A_IN_ASCII 32
struct Customer
{
	int id;
	char* customerName; //dynaminc string

	char creditCardNumber[MAX_INPUT_CREDIT_CARD_LENGTH]; //i will take just 12 digits anyway.
	int creditCardYearValidity;
	int creditCardMonthValidity;

}typedef customer_t;

void printCustomerArray(const customer_t*** customersArray, int* sizeOfCustomersArray);

void addCustomer(customer_t*** customersArray, customer_t* customer, int* sizeOfCustomerArray);

void initialCustomer(customer_t* customer);
void setCustomerName(customer_t* customer);
void setCustomerCreditCard(customer_t* customer);

void freeCustomers(customer_t*** customersArray,int* sizeOfCustomerArray);
void updtateCustomersToCapital(customer_t*** customersArray, int* sizeOfCustomerArray);


customer_t** custmersNameSubString(customer_t** customersArray, 
	int* sizeOfSubStringNamesArray, int* sizeOfCustomerArray, char* subStringToCheck);

#endif
