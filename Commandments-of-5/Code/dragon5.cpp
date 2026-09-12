#include <stdio.h>
#include <stdlib.h>

int main()
{
    //unsigned int sum = 2000000000 + 2000000000;  /* 超出 int 存放範圍 */
    //unsigned int sum = (unsigned int) (2000000000 + 2000000000);
    unsigned int sum = (unsigned int) 2000000000 + 2000000000;
    
    printf("sum:%u\n", sum);
	
	return 0;
}
