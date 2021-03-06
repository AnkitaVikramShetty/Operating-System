#include <xinu.h>
#include <queue_temp.h>
#include <future.h>

syscall future_free(future* f)
{
	intmask mask;
	mask = disable();
	int r = freemem((char*)f,sizeof(future));
	restore(mask);
	if(r == SYSERR)
		return SYSERR;
	else
		return OK;
}

