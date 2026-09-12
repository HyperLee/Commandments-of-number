#include <stdio.h>
#include <stdlib.h>
int* createNewArray(int size) {
        return (int*) malloc( size * sizeof(int) );
    }
    
        
int main()
{
	int i = 0;
	int* ptr;
	ptr = createNewArray(10);
	//newArray(ptr, 10);
	
	for(i = 0; i < 10 ; i++)
	{
		*(ptr + i) = i;
		printf("ptr + %d = %d\n", i, *(ptr + i));
	}
	
	
    system("pause");
	return 0;
}
