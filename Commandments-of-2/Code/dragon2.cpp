#include <stdio.h>
#include <stdlib.h>

 main(void)
{
	char name[21];   /* Max Length 20¡A one empty '\0' */
    printf("Your name, please: ");
    gets(name);
    printf("Hello, %s\n", name);
	return 0;
}
