
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "defs.h"
#include "_journey.c"

/*	Read input data from file
 *	Return value: 
 *		0: fail	
 *		1: successful
 */
int readFile(struct musketeer* theMusketeer, int* R, int* N, int* nEvent, int arrEvent[], char* file_name)
{
	FILE* f = 0;	
	char* str = (char*) malloc(MAX_CHARACTER_EACH_LINE * sizeof(char));
	int start, len, num;

	//printf("%s\n", file_name);
	f = fopen(file_name, "r");
	if (f == NULL)
		return 0;
	
	//read R
	if (feof(f))
		return 0;
	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	//fscanf(f, "%s", str);
	if (str == NULL)
		return 0;
	start = 0;
	len = strlen(str);
	while (start < len && str[start] == ' ')
		start ++;
	if (start >= len)
		return 0;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start] - '0';
		start++;
	}
	*R = num;
	if (*R < 0 || *R > 10)
		return 0;
	
	//read N
	if (feof(f))
		return 0;
	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	if (str == NULL)
		return 0;
	start = 0;
	len = strlen(str);
	while (start < len && str[start] == ' ')
		start ++;
	if (start >= len)
		return 0;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start] - '0';
		start++;
	}
	*N = num;
	if (*N < 1 || *N > 99)
		return 0;

	//read ID
	if (feof(f))
		return 0;
	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	if (str == NULL)
		return 0;
	start = 0;
	len = strlen(str);
	while (start < len && str[start] == ' ')
		start ++;
	if (start >= len)
		return 0;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start] - '0';
		start++;
	}
	theMusketeer->ID = num;
	if (theMusketeer->ID < 1 || theMusketeer->ID > 4)
		return 0;

	//read nGoldCoin (M)
	if (feof(f))
		return 0;
	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	if (str == NULL)
		return 0;
	start = 0;
	len = strlen(str);
	while (start < len && str[start] == ' ')
		start ++;
	if (start >= len)
		return 0;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start] - '0';
		start++;
	}
	theMusketeer->nGoldCoin = num;
	if (theMusketeer->nGoldCoin < 0 || theMusketeer->nGoldCoin > 999)
		return 0;

	//read nEvent, arrEvent
	*nEvent = 0;
	//arrEvent[0] = 0;
	if (feof(f))
		return 0;
	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	if (str == NULL)
		return 0;
	start = 0;
	len = strlen(str);
	while (start < len) {
		while (start < len && (str[start] > '9' || str[start] < '0'))
			start ++;
		if (start >= len)
			break;
		*nEvent = *nEvent + 1;
		//printf("nEvent = %d\n", *nEvent);
		arrEvent[*nEvent] = 0;
		while (start < len && str[start] <= '9' && str[start] >= '0') {
			arrEvent[*nEvent] = arrEvent[*nEvent] * 10 + str[start] - '0';
			start++;
		}		
		//*nEvent = *nEvent + 1;
		//arrEvent[*nEvent] = 0;
	}	
	
	fclose(f);
	free(str);

	return 1;
}

/*	Display the output on screen
 *	Return value: 
 *		Void
 */
void display(int nOut) 
{
	printf("\n%d", nOut);
}

int main(int argc, char *argv[])
{
	struct musketeer theMusketeer; 
	int R, N; 
	int nEvent; // the number of events
	int arrEvent[EVENT_SIZE]; // used to save events
	int nOut; // output value	

	//if(readFile(&theMusketeer, &R, &N, &nEvent, arrEvent, argv[1]))

	if(readFile(&theMusketeer, &R, &N, &nEvent, arrEvent, "input.txt"))
	{
		nOut = calculate(theMusketeer, R, N, nEvent, arrEvent);
		display(nOut); 	
	}
	else
		printf("Error reading file");

	return 1;
}

