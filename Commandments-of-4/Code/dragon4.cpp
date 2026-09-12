#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 main(void)
{
	//char *s1 = "hello, ";
    char s1[20] = "Hello, ";
    char *s2 = "world!";
    /* 因為 strcat() 的返回值等於第一個參數值，所以 s3 就不需要了 */
    strcat(s1, s2);
	printf("%s\n", s1);
    
	
    system("pause");
	return 0;
}
