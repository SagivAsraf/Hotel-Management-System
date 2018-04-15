#include "Customer.h"
#pragma warning (disable:4996)


void addCustomer(customer_t*** customersArray, customer_t* customer, int* sizeOfCustomerArray) {

	customer = (customer_t*)calloc(1, sizeof(customer_t));
	if (!customer)//--> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return;
	}


	initialCustomer(customer);

	*sizeOfCustomerArray = customer->id;

	//when new customer is arrive, we will increase the array with realloc
	(*customersArray) = (customer_t**)realloc(*customersArray, (*sizeOfCustomerArray) * (sizeof(customer_t*)));


	if (!*customersArray)//--> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return;
	}

	(*customersArray)[(*sizeOfCustomerArray) - 1] = customer; //put the customer into the array

}

void initialCustomer(customer_t* customer) {

	static int sid = 0; //static variable. cause the sid is static,every customer has unique id

	sid++;

	customer->id = sid;
	setCustomerName(customer);
	//printf("%s \n", customer->customerName);// just check.
	setCustomerCreditCard(customer);
	//printf("%s \n", customer->creditCardNumber);// just check.

}

/*Helper method for print the array*/

void printCustomerArray(const customer_t*** customersArray, int* sizeOfCustomersArray) {
	int i;

	for (i = 0; i < *sizeOfCustomersArray; i++)
	{
		printf("\nThe %d custmer id is: %d ,|| Name is: %s\n", i + 1, (*customersArray)[i]->id,
			(*customersArray)[i]->customerName);
	}
}


/*Helper method for set customer name*/
void setCustomerName(customer_t* customer) {

	char tmp[MAX_LENGTH_CUSTOMER_NAME]; //maximum of chars for name...

	printf("Please enter a name for the customer max %d chars \n", MAX_LENGTH_CUSTOMER_NAME);
	scanf("%s", tmp);
	int customerNameLength = strlen(tmp) + 1; // +1 for null terminate
	printf("customer name length is: %d chars \n", customerNameLength);

	customer->customerName = (char*)calloc(customerNameLength, sizeof(char));
	if (!customer->customerName)//--> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return;
	}
	strcpy(customer->customerName, tmp);

}
/*Helper method for set credit card (number,month and year)*/
void setCustomerCreditCard(customer_t* customer)
{

	int legal = 0;
	printf("Please enter number of creditCard (%d digits exactly) \n", CREDIT_CARD_LENGTH);
	char creditCardNumber[MAX_INPUT_CREDIT_CARD_LENGTH]; //I WILL TAKE 12 digits for credit card number 
	do
	{
		scanf("%s", creditCardNumber);
		if (strlen(creditCardNumber) != CREDIT_CARD_LENGTH) {
			printf("Wrong number, please enter %d digits.\n", CREDIT_CARD_LENGTH);
		}
		else {
			legal = 1;
			strcpy(customer->creditCardNumber, creditCardNumber);
		}
	} while (legal == 0);

	int yearCreditCard, monthCreditCard;
	legal = 0;
	printf("Please enter month of the date valid credit card :(1-12) \n");
	do
	{
		scanf("%d", &monthCreditCard);
		if (monthCreditCard < 1 || monthCreditCard > 12) {
			printf("Wrong number, num between 1-12 \n");
		}
		else {
			legal = 1;
			customer->creditCardMonthValidity = monthCreditCard;
		}
	} while (legal == 0);

	legal = 0;
	printf("Please enter year of the date valid credit card %d-%d \n", MIN_YEAR_CARD, MAX_YEAR_CARD);
	do
	{
		scanf("%d", &yearCreditCard);
		if (yearCreditCard < MIN_YEAR_CARD || yearCreditCard > MAX_YEAR_CARD) {
			printf("Wrong number, please enter num between %d-%d \n", MIN_YEAR_CARD, MAX_YEAR_CARD);
		}
		else {
			legal = 1;
			customer->creditCardYearValidity = yearCreditCard;
		}
	} while (legal == 0);

}
/*Update all the customers in the hotel name's to begin with capital letter*/

void updtateCustomersToCapital(customer_t*** customersArray, int* sizeOfCustomersArray) {

	int i;
	if (*sizeOfCustomersArray != 0)
	{
		for (i = 0; i < *sizeOfCustomersArray; i++)
		{
			if ((*customersArray)[i]->customerName[0] >= 'a' &&
				((*customersArray)[i]->customerName[0] <= 'z'))
			{
				(*customersArray)[i]->customerName[0] -= DIFFERENCE_BETWEEN_A_TO_A_IN_ASCII;
			}
		}
	}
	else
	{
		printf("No customers to change \n");
	}
}

/*Method that find all the names of the customers that include the subString the user press in*/
customer_t** custmersNameSubString(customer_t** customersArray, int* sizeOfSubStringNamesArray, int* sizeOfCustomerArray
	, char* subStringToCheck) {

	customer_t** customersWithSubStringArray = NULL;
	int i;
	for (i = 0; i < *sizeOfCustomerArray; i++)
	{
		if (strstr((customersArray[i]->customerName), subStringToCheck) != NULL)
			// check sub string in there...
		{
			(*sizeOfSubStringNamesArray)++;
			customersWithSubStringArray = (customer_t**)realloc(customersWithSubStringArray, (*sizeOfSubStringNamesArray) * (sizeof(customer_t*)));
			customersWithSubStringArray[(*sizeOfSubStringNamesArray) - 1] = customersArray[i];
		}
	}
	return customersWithSubStringArray;
}

void freeCustomers(customer_t*** customersArray, int* sizeOfCustomerArray) {

	int i;
	for (i = 0; i < *sizeOfCustomerArray; i++)
	{
		free((*customersArray)[i]->customerName);
		free((*customersArray)[i]);
	}
}
