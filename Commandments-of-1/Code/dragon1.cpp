#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char name[20];
	printf("enter ypur name: ");
	//scanf("%s", name);
	fgets(name,20,stdin);
	printf("hello ,%s\n", name);
	
	
	system("pause");
	return 0;
	
}
