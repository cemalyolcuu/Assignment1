#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FlightInfo
{
	char* destination;
	char* date;
	float fare;
} FlightInfo;

typedef struct FlightNode
{
	FlightInfo flight;
	struct FlightNode* prev;
	struct FlightNode* next;
} FlightNode;

FlightNode* createFlightNode(char* destination, char* date, float fare)
{
	FlightNode* newNode = (FlightNode*)malloc(sizeof(FlightNode));

	if (newNode == NULL)
	{
		return NULL;
	}

	newNode->flight.destination = (char*)malloc(strlen(destination) + 1);
	newNode->flight.date = (char*)malloc(strlen(date) + 1);

	if (newNode->flight.destination == NULL || newNode->flight.date == NULL)
	{
		free(newNode->flight.destination);
		free(newNode->flight.date);
		free(newNode);
		return NULL;
	}

	strcpy_s(newNode->flight.destination, strlen(destination) + 1, destination);
	strcpy_s(newNode->flight.date, strlen(date) + 1, date);

	newNode->flight.fare = fare;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

int main(void)
{

	return 0;
}
