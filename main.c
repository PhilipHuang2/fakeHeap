#include<stdio.h>
#define ALLOCATED "allocated\n"
#define FREE "free\n"

int heap[128];

int main()
{
	heap[0] = 254;
	printf("Hello, World.\n");
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
