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

void insertSortedByDestination(FlightNode** head, FlightNode** tail, FlightNode* newNode)
{
	FlightNode* current;

	if (newNode == NULL)
	{
		return;
	}

	current = *head;

	if (*head == NULL)
	{
		*head = newNode;
		*tail = newNode;
		return;
	}

	while (current != NULL && strcmp(current->flight.destination, newNode->flight.destination) <= 0)
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
	FlightNode* fareHead = NULL;
	FlightNode* fareTail = NULL;
	FlightNode* destinationHead = NULL;
	FlightNode* destinationTail = NULL;

	FlightNode* fareNode;
	FlightNode* destinationNode;
	FlightNode* current;
	FlightNode* next;

	char destination[15];
	char date[9];
	float fare;

	while (1)
	{
		if (fgets(destination, sizeof(destination), stdin) == NULL)
		{
			break;
		}

		destination[strcspn(destination, "\n")] = '\0';

		if (strcmp(destination, ".") == 0)
		{
			break;
		}

		if (fgets(date, sizeof(date), stdin) == NULL)
		{
			break;
		}

		date[strcspn(date, "\n")] = '\0';

		if (strcmp(date, ".") == 0)
		{
			break;
		}

		if (scanf_s("%f", &fare) != 1)
		{
			break;
		}

		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		{
		}

		fareNode = createFlightNode(destination, date, fare);
		destinationNode = createFlightNode(destination, date, fare);

		if (fareNode == NULL || destinationNode == NULL)
		{
			if (fareNode != NULL)
			{
				free(fareNode->flight.destination);
				free(fareNode->flight.date);
				free(fareNode);
			}

			if (destinationNode != NULL)
			{
				free(destinationNode->flight.destination);
				free(destinationNode->flight.date);
				free(destinationNode);
			}

			break;

		}

		insertSortedByFare(&fareHead, &fareTail, fareNode);
		insertSortedByDestination(&destinationHead, &destinationTail, destinationNode);

	}

	

	current = fareHead; /* free fare sorted list */

	while (current != NULL)
	{
		next = current->next;
		free(current->flight.destination);
		free(current->flight.date);
		free(current);
		current = next;
	}

	current = destinationHead; /* free destination sorted list */

	while (current != NULL)
	{
		next = current->next;
		free(current->flight.destination);
		free(current->flight.date);
		free(current);
		current = next;
	}



	return 0;
}
