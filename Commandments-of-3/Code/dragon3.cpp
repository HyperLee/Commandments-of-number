#include <stdio.h>
#include <stdlib.h>

 main(void)
{
	//char* pc = "john";
	//printf("%s", pc);
	
	//*pc = "J";
	//prinf("%s\n", pc);
	
	////////// up error /////////////////
	
	char pc[] = "john";
	printf("%s ", pc);
    *pc = 'J';
    //pc[2] = 'H';
    printf("%s ", pc);
    
	
    system("pause");
	return 0;
}
