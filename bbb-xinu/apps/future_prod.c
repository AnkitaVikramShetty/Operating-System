#include <prodcons.h>

int future_prod(future *fut) 
{
	int i, j;
	j = (int)fut;
	for(i=0 ; i<1000 ; i++) 
	{
		j += i;
	}
	future_set(fut, &j);
	//if(fut->flag == FUTURE_SHARED || fut->flag == FUTURE_EXCLUSIVE)
	//	future_free(fut);
	return OK;
}
