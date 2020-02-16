#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define ALLOCATED "allocated\n"
#define FREE "free\n"

int heap[128];


typedef struct { char* str; char c;} str_char_Map;

str_char_Map caseTable[] = {
	{"malloc", 'm'}, {"free", 'f'}, {"blocklist", 'b'}, 
	{"writemem", 'w'}, {"printmem", 'p'}
};

char casefromstr(char *key);
void errMsgArg();
#define BADKEY 'x'


void _malloc(int space_needed);
void _free();
void blocklist();
void writemem();
void printmem();

int main()
{
	heap[0] = 254;
	printf("Hello, World.\n");

	char input[90];
	char * token;
	char* argv[20];
	const char * str = " \n";
	int argCount = 0;
	int a_count = 0;

do
	{
		printf(">");
		fgets(input, 90, stdin);

		// printf("%s", input);

		token = strtok(input,str);
		argv[0] = token;
		while ( token != NULL){

			token = strtok(NULL, str);
			argv[++argCount] = token;
			
		}
		
		// do{			//prints the arguments of the command
		// 	printf("[%s][%d]\n",argv[a_count],a_count);
		// 	a_count++;
		// }while (argv[a_count] != NULL);
		
		switch (casefromstr(argv[0])){
			case 'm':					//malloc
					if (argCount == 2){
						_malloc(atoi(argv[1]));
					}
					//else
						//errMsgArg();
				break;
			case 'f':					//free
					//if (argCount == 3){
					_free();
					//}
					//else 
						//errMsgArg();
				break;
			case 'b':					//blocklist
					//if (argCount == 2){
						blocklist();
					//}
					//else 
						//errMsgArg();
				break;
			case 'w':					//writemem
					//if (argCount == 2){
						writemem(); 	//showDisk(atoi(argv[1]));
					//}
					//else
						//errMsgArg();
				break;
			case 'p':					//printmem
					//if (argCount == 1){
						printmem();
					//}
					//else
						//errMsgArg();
				break;
		
		}
		//resets to the start of the argv array
		if (argv[argCount] == NULL){
			argCount = 0;
			a_count = 0;
		}
	}while(strcmp(input,"quit") != 0);
}


void _malloc(int space_needed){
	int count = 0;
	int nextBest = -1;
	int payload_length;
	int allocated;
	
	// iterate through the free implicit list
	while(count < 127){
		payload_length = heap[count]/2;
		allocated = heap[count] % 2;
		// only work with unallocated blocks
		if(allocated == 0)
		{
			// if block is too small, ignore it.

			// if the block is perfect, allocated it and return it.
			if((payload_length - 1) == space_needed)
			{
				heap[count] = heap[count] | 1;
				printf("%d\n",count + 1);
			}
			// if block is too big, compare it to the stored block and save the smaller one 
			if((payload_length - 1) > space_needed)
			{
				// if empty, initialize
				if(nextBest = -1)
					nextBest = count;

				if ((heap[nextBest] / 2) > payload_length)
					nextBest = count;			
			}
		}
		// Move through block based on the payload size
		count = count + payload_length;		
	}
	// This code assumes that the saved block is bigger than needed or -1;
	if(nextBest == -1)
	{
		printf("No available blocks to malloc.\n");
		printf("%d\n",-1);
	}
	space_needed++;
	int oldSize = heap[nextBest] >> 1;
	int newHeader = (space_needed << 1) | 1;
	// printf("oldSize: %d, newSize: %d\n", oldSize, space_needed);
	heap[nextBest] = newHeader;
	heap[nextBest + space_needed] = (oldSize - space_needed) << 1;
	// printf("old Value: %d, new Value: %d\n", heap[nextBest], heap[nextBest + space_needed]);
	printf("%d\n", nextBest + 1);
}
void _free(){
	printf("free function\n");
}
void blocklist(){
	int count = 0;
	int payload_length;
	int allocated;
	while(count < 127)
	{
		payload_length= heap[count]/2;
		allocated= heap[count] % 2;
		if(allocated)
			printf("%d, %d, %s", count + 1, payload_length - 1, ALLOCATED);
		else
			printf("%d, %d, %s", count + 1, payload_length - 1, FREE);
			
		count = count +  payload_length;
	}	
}
void writemem(){
	printf("writemem function\n");
}
void printmem(){
	printf("printmem function\n");
}


void errMsgArg(){
	printf("Error: Incorrect number of arguments!\n");
}

char casefromstr(char *key)
{
    int i;
    for (i=0; i < 5; i++) {
        //str_char_Map *map = caseTable[i];
        if (strcmp(caseTable[i].str, key) == 0)
            return caseTable[i].c;
    }
    return BADKEY;
}