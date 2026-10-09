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

int main(void)
{



	return 0;
}
