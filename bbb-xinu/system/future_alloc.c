#include <xinu.h>
#include <queue_temp.h>
#include <future.h>

future* future_alloc(int future_flag)
{
	intmask mask;
	mask = disable();
	future* f = (future*)getmem(sizeof(future)); 

	if(SYSERR == (int)f)
	{
		restore(mask);
		return NULL;
	}
	else
	{
		f->state = FUTURE_EMPTY;
		f->flag = future_flag;
		
		// for future shared
		(f->set_queue).front = NULL;
		(f->set_queue).rear = NULL;
		(f->get_queue).front = NULL;
		(f->get_queue).rear = NULL;
		restore(mask);
		return f;
	}
}
