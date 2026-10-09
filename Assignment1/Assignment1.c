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

void insertSortedByFare(FlightNode** head, FlightNode** tail, FlightNode* newNode)
{
	FlightNode* current = *head;

	if (*head == NULL)
	{
		*head = newNode;
		*tail = newNode;
		return;
	}

	while (current != NULL && current->flight.fare <= newNode->flight.fare)
	{
		current = current->next;
	}

	if (current == *head)
	{
		newNode->next = *head;
		(*head)->prev = newNode;
		*head = newNode;

	}
	else if (current == NULL)
	{
		newNode->prev = *tail;
		(*tail)->next = newNode;
		*tail = newNode;
	}
	else
	{
		newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;
	}
}

int main(void)
{

	


	return 0;
}
