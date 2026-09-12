#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i = 0;
	//int array[10000000];
	int *array = (int*) malloc( 10000000*sizeof(int) );
	
	for(i = 0; i < 10000000; i++)
	{
		array[i] = i;
		printf("array[%d] %d\n", i, array[i]);
	}
	
	
    system("pause");
	return 0;
}
