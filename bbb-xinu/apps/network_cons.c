#include <prodcons.h>

int network_cons(future *fut) 
{
	int i, status;
	status = future_get(fut, &i);
	if (status < 1) {
		kprintf("future_get failed\n");
		return -1;
	}
	kprintf("Consumer consumed %d\n", i);
	return OK;
}

