/*
* FILE			: Assignment1.c
* PROJECT		: DATA STRUCTURE, Assignment 1
* PROGRAMMER	: Cemal Yolcu
* FIRST VERSION	: 2026-10-09
* DESCRIPTION	:
*	This program stores flight information using two
*	sorted doubly linked lists. One list is sorted by
*	fare and the other is sorted by destination.
*	The program supports flight searching, fare updates,
*	and dynamic memory cleanup.
*/


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



/*
 * FUNCTION    : createFlightNode
 * DESCRIPTION :
 *     Allocates memory for a new flight node and its
 *     destination and date strings.
 * PARAMETERS  :
 *     char* destination : Flight destination
 *     char* date        : Flight date
 *     float fare        : Flight fare
 * RETURNS     :
 *     FlightNode* : Pointer to the new node, or NULL
 *                   if memory allocation fails.
 */

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


/*
 * FUNCTION    : insertSortedByFare
 * DESCRIPTION :
 *     Inserts a flight node into the doubly linked list
 *     in ascending order by fare.
 * PARAMETERS  :
 *     FlightNode** head : Pointer to the list head
 *     FlightNode** tail : Pointer to the list tail
 *     FlightNode* newNode : Node to insert
 * RETURNS     :
 *     void : No return value
 */

void insertSortedByFare(FlightNode** head, FlightNode** tail, FlightNode* newNode)
{
	FlightNode* current = *head;

	if (newNode == NULL)
	{
		return;
	}

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


/*
 * FUNCTION    : insertSortedByDestination
 * DESCRIPTION :
 *     Inserts a flight node into the doubly linked list
 *     in ascending alphabetical order by destination.
 * PARAMETERS  :
 *     FlightNode** head : Pointer to the list head
 *     FlightNode** tail : Pointer to the list tail
 *     FlightNode* newNode : Node to insert
 * RETURNS     :
 *     void : No return value
 */

void insertSortedByDestination(FlightNode** head, FlightNode** tail, FlightNode* newNode)
{
	FlightNode* current = *head;

	if (newNode == NULL)
	{
		return;
	}

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


/*
 * FUNCTION    : displayList
 * DESCRIPTION :
 *     Displays all flights in the linked list, including
 *     destination, date, and fare.
 * PARAMETERS  :
 *     FlightNode* head : Head of the list to display
 * RETURNS     :
 *     void : No return value
 */

void displayList(FlightNode* head)
{
	FlightNode* current = head;

	while (current != NULL)
	{
		printf("%-15s%-10s%-10.2f\n", 
			current->flight.destination, 
			current->flight.date, 
			current->flight.fare);

		current = current->next;
	}
}


/*
 * FUNCTION    : findFlight
 * DESCRIPTION :
 *     Searches the linked list for a flight matching
 *     both the destination and date.
 * PARAMETERS  :
 *     FlightNode* head : Head of the list to search
 *     char* destination : Destination to find
 *     char* date        : Date to find
 * RETURNS     :
 *     FlightNode* : Pointer to the matching node,
 *                   or NULL if no match is found.
 */

FlightNode* findFlight(FlightNode* head, char* destination, char* date)
{
	FlightNode* current = head;

	while (current != NULL)
	{
		if (strcmp(current->flight.destination, destination) == 0 &&
			strcmp(current->flight.date, date) == 0)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}


/*
 * FUNCTION    : deleteNode
 * DESCRIPTION :
 *     Removes a node from the doubly linked list,
 *     updates the surrounding links and list pointers,
 *     and frees the allocated memory.
 * PARAMETERS  :
 *     FlightNode* node  : Node to delete
 *     FlightNode** head : Pointer to the list head
 *     FlightNode** tail : Pointer to the list tail
 * RETURNS     :
 *     void : No return value
 */

void deleteNode(FlightNode* node, FlightNode** head, FlightNode** tail) 
{
	if (node == NULL)
	{
		return;
	}

	if (node->prev != NULL)
	{
		node->prev->next = node->next;
	}
	else
	{
		*head = node->next;
	}

	if (node->next != NULL)
	{
		node->next->prev = node->prev;
	}
	else
	{
		*tail = node->prev;
	}

	free(node->flight.destination);
	free(node->flight.date);
	free(node);

}



int main(void)
{
	FlightNode* fareHead = NULL;
	FlightNode* fareTail = NULL;
	FlightNode* destinationHead = NULL;
	FlightNode* destinationTail = NULL;

	FlightNode* fareNode = NULL;
	FlightNode* destinationNode = NULL;
	FlightNode* foundFlight = NULL;
	FlightNode* fareMatch = NULL;
	FlightNode* updatedNode = NULL;

	float newFare = 0.0f;

	char destination[16] = { 0 };
	char date[10] = { 0 };
	float fare = 0.0f;


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

		int ch = 0;
		while ((ch = getchar()) != '\n' && ch != EOF)
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

	displayList(fareHead);
	displayList(destinationHead);




	/* Search for a flight to update its fare */

	if (fgets(destination, sizeof(destination), stdin) != NULL)
	{
		destination[strcspn(destination, "\n")] = '\0';

		if (fgets(date, sizeof(date), stdin) != NULL)
		{
			date[strcspn(date, "\n")] = '\0';

			foundFlight = findFlight(destinationHead, destination, date);

			if (foundFlight == NULL)
			{
				printf("Flight not found.\n");
			}
			else
			{
				printf("Current fare: %.2f\n", foundFlight->flight.fare);
				printf("Enter new fare:\n");

				if (scanf_s("%f", &newFare) == 1)
				{
					if (newFare == foundFlight->flight.fare)
					{
						printf("Fare unchanged.\n");
					}
					else
					{
						fareMatch = findFlight(fareHead, destination, date);

						if (fareMatch != NULL)
						{
							updatedNode = createFlightNode(destination, date, newFare);

							if (updatedNode != NULL)
							{
								foundFlight->flight.fare = newFare;

								deleteNode(fareMatch, &fareHead, &fareTail);

								insertSortedByFare(&fareHead, &fareTail, updatedNode);
							}
						}
					}
				}
			}
		}
	}

	/* Display both lists after the update */

	displayList(fareHead);
	displayList(destinationHead);



	/* Free fare sorted list */
	while (fareHead != NULL)
	{
		deleteNode(fareHead, &fareHead, &fareTail);
	}

	/* Free destination sorted list */
	while (destinationHead != NULL)
	{
		deleteNode(destinationHead, &destinationHead, &destinationTail);
	}




	return 0;
}
