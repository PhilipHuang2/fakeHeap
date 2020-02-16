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


void _malloc();
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
					//if (argCount == 2){
						_malloc();
					//}
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


	int count =0;
	while(count <= 127)
	{
		int payload_length = heap[count]/2;
		int allocated = heap[count] % 2;
		if(allocated)
			printf("%d, %d, %s", count + 1, payload_length - 1, ALLOCATED);
		else
			printf("%d, %d, %s", count + 1, payload_length - 1, FREE);
			
		count = count +  payload_length + 1;
	}	

}


void _malloc(){
	printf("malloc function\n");
}
void _free(){
	printf("free function\n");
}
void blocklist(){
	printf("blocklist function\n");
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