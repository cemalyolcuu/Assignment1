# Assignment 1 – Sorted Doubly Linked Lists

**Course:** SENG1050 – Data Structures  
**Student:** Cemal Yolcu  
**Language:** C  
**Development Environment:** Visual Studio 2026

## Description

This program manages flight information using two separate sorted doubly linked lists.

Each flight contains:
- Destination
- Date (DDMMYYYY)
- Fare

One linked list is sorted by fare in ascending order, while the other is sorted alphabetically by destination.

## How to Run

1. Open the Assignment1 project in Visual Studio.
2. Build and run the program.
3. Enter each flight's destination, date, and fare on separate lines.
4. Enter a single period (`.`) as the destination or date to finish adding flights.
5. The program displays both sorted lists.
6. Enter the destination and date of a flight to search for.
7. If the flight is found, its current fare is displayed and a new fare is requested.
8. The program displays both lists again and exits.

**Note:** The console does not display prompts during the initial flight entry. Enter the values in the order described above.

## Example Input

Enter the following values, one per line:

```text
Toronto
15102026
350.50
Ottawa
18102026
150.00
Vancouver
20102026
600.00
.
Toronto
15102026
700.00
```

The period ends the initial flight-entry process. The final three lines search for the Toronto flight on October 15, 2026, and update its fare to 700.00.

## Expected Result

After the fare update, the fare-sorted list is:

```text
Ottawa         18102026  150.00
Vancouver      20102026  600.00
Toronto        15102026  700.00
```

The destination-sorted list is:

```text
Ottawa         18102026  150.00
Toronto        15102026  700.00
Vancouver      20102026  600.00
```

## Implementation

The program uses dynamic memory allocation, structs, and doubly linked lists. It supports sorted insertion, searching for flights by destination and date, updating fares, deleting nodes, and freeing allocated memory.

**Input Requirements:** Destination and date comparisons are case-sensitive. The program expects valid flight data as specified in the assignment instructions.
