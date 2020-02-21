#include <stdio.h>
#include <string.h>
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
void _free(int allocated_payload);
void blocklist();
void writemem(int address, char* str);
void printmem(int address, int length);

int is_alloc(int address);
int get_header(int address);

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
					else
						errMsgArg();
				break;
			case 'f':					//free
					if (argCount == 2){
					_free(atoi(argv[1]));
					}
					else 
						errMsgArg();
				break;
			case 'b':					//blocklist
					//if (argCount == 2){
						blocklist();
					//}
					//else 
						//errMsgArg();
				break;
			case 'w':					//writemem
					if (argCount == 3){
						writemem(atoi(argv[1]),argv[2]); 	//showDisk(atoi(argv[1]));
					}
					else
						errMsgArg();
				break;
			case 'p':					//printmem
					if (argCount == 3){
						printmem(atoi(argv[1]),atoi(argv[2]));
					}
					else
						errMsgArg();
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
	if(space_needed < 0)
		return;

	int count = 0;
	int nextBest = -1;
	int payload_length;
	int allocated;
	
	// iterate through the free implicit list
	while( count < 127){
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
	// if(nextBest == -1)
	// {
	// 	printf("No available blocks to malloc.\n");
	// 	printf("%d\n",-1);
	// }
	space_needed++;
	int oldSize = heap[nextBest] >> 1;					//divide
	int newHeader = (space_needed << 1) | 1;			//multi, OR 1
	// printf("oldSize: %d, newSize: %d\n", oldSize, space_needed);
	heap[nextBest] = newHeader;
	//printf("newHeader:%d \n",newHeader);
	heap[nextBest + space_needed] = (oldSize - space_needed) << 1;
	// printf("old Value: %d, new Value: %d\n", heap[nextBest], heap[nextBest + space_needed]);
	printf("%d\n", nextBest + 1);
}
void _free(int allocated_payload){
	//allocated_payload is the pointer to a prev allocated block of memory

	int size = (heap[allocated_payload-1]/2);		//-1 for the allocated size
	int allocated = heap[allocated_payload-1] % 2;
	int next = size + allocated_payload;
	int value = heap[allocated_payload-1];
	// printf("payload_length: %d \n",size);
	// printf("allocated?: %d \n",allocated);
	// printf("next: %d \n",next);
	// printf("value: %d \n",value);
	if (allocated){
		heap[allocated_payload-1] = heap[allocated_payload-1] - 1;
	}
	if (is_alloc(next) == 0){
		heap[allocated_payload-1]+= heap[next-1]; 		//new value
		
	}
	//iterate the payload and set 0



	int limit = allocated_payload + (heap[allocated_payload-1]/2);
	int count = allocated_payload;
	while (count < (limit -1)){
		heap[count] = 0;
		count++;
	}
	// printf("heap[allocated_payload-1]: %d \n",heap[allocated_payload-1]);
	// printf("heap[next]: %d \n",heap[next]);
	// printf("heap[next-1]: %d \n",heap[next-1]);

	//printf("free function\n");
}

int is_alloc(int address){
	return heap[address-1] % 2;
}

void blocklist(){
	int count = 0;
	int payload_length;
	int allocated;
	while(count < 127)
	{
		payload_length= heap[count]/2;
		allocated= heap[count] % 2;
		// printf("payload_length: %d \n",payload_length);
		// printf("allocated?: %d \n",allocated);
		//printf("heap[count]: %d , count: %d\n",heap[count], count);
		if(allocated)
			printf("%d, %d, %s", count + 1, payload_length - 1, ALLOCATED);
		else
			printf("%d, %d, %s", count + 1, payload_length - 1, FREE);
			
		//printf("current count: %d \n",count);
		if (payload_length == 0){
			return;
		}
		count = count +  payload_length;

		//printf("next count: %d \n",count);	
	}	
}
void writemem(int address, char* str){
	char tok;
	int len = strlen(str);
	int str_count = 0;

	int limit = address + len;



	while (address < limit){
		heap[address] = (int) str[str_count];

		printf("%02X \n",heap[address]);

		address++;
		str_count++;
	}

	printf("writemem - arg1: %d, arg2:%s\n", address, str);
	printf("limit: %d\n",limit);

}

int get_header(int address){
	int count = 0;
	int payload_length;

	while(count < 127)
	{
		payload_length = heap[count]/2;
		
		if (address > count && address < count +  payload_length){
			return count;
		}

		count = count +  payload_length;
		
	}	
	return -1;	//return if header not found
}


void printmem(int address, int length){
	int count = 0;
	while(count < length)
	{
		printf("%02X ",heap[address+count]);
		count++;
	}
	printf("\n");
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