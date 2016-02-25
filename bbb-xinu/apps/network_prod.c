#include <prodcons.h>

int network_prod(future *fut) 
{
	int j;
	//j=0;
	j = netvalue();
	if(j > -1)
	{
		future_set(fut, &j);
		return OK;
	}
	else
	{
		printf("future get failed");
		return SYSERR;
	}
}
