#include <stdio.h>

int discrim(int, int, int);

int main()
{
	int a,b,c,d;
	int i=0;

	while(i<3)
	{
		printf("Please enter vals:");
		scanf("%d %d %d",&a,&b,&c);
		d=discrim(a,b,c);
		printf("The discrim is %d \n",d);
		i++;
	}


}
