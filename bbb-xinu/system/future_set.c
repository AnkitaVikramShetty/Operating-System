#include <xinu.h>
#include <queue_temp.h>
#include <future.h>

syscall future_set(future *f, int *value)
{
	intmask mask;	
	mask = disable();

	if(f == NULL)
	{	
		restore(mask);
		return SYSERR;
	}
	if(f->flag == FUTURE_EXCLUSIVE) 
	{
		if(f->state == FUTURE_WAITING)
		{
			f->value = value;
			f->state = FUTURE_VALID;
			//printf("in set : %d \n",*f->value);
			resume(f->tid);
			restore (mask);
			return OK;
		}
		else if(f->state == FUTURE_EMPTY)
		{
			f->value = value;
			f->state = FUTURE_VALID;
			restore (mask);
			return OK;	
		}
	}
	else if(f->flag == FUTURE_SHARED)
	{
		count_shared++;
		if(count_shared == 1)
		{
			if(f->state == FUTURE_WAITING)
			{
				f->value = value;
				f->state = FUTURE_VALID;
				//printf("in set : %d \n",*f->value);
			
				while((f->get_queue).front != NULL)
					resume(dequeue_temp(&(f->get_queue)));			
			
				restore (mask);
				return OK;
			}
			else if(f->state == FUTURE_EMPTY)
			{
				f->value = value;
				f->state = FUTURE_VALID;
				restore (mask);
				return OK;	
			}
		}
		else
		{
			printf("Only one producer allowed\n");
			restore(mask);
			return SYSERR;
		}
	}
	else if(f->flag == FUTURE_QUEUE)
	{
		if(f->state == FUTURE_WAITING)
		{
			f->value = value;
			f->state = FUTURE_VALID;
			//printf("in set : %d %d\n",*f->value,currpid);
		
			resume(dequeue_temp(&(f->get_queue)));			
			
			if((f->get_queue).front == NULL)
				f->state = FUTURE_EMPTY;
			else
				f->state = FUTURE_WAITING;
	
			restore (mask);
			return OK;
		}
		else if((f->state == FUTURE_EMPTY) || (f->state == FUTURE_VALID))
		{
			f->tid = currpid;
			enqueue_temp(f->tid, &(f->set_queue));	
			suspend(f->tid); 
			f->value = value;
			f->state = FUTURE_VALID;
			//printf("in set : %d %d\n",*(f->value),currpid);
			restore (mask);
			return OK;	
		}
	
	}
	restore(mask);
	return SYSERR;
}
