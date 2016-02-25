#include <xinu.h>
#include <queue_temp.h>
#include <future.h>

void enqueue_temp(pid32 key, queue *queue_type)
{
	node *tmp_node = (node *)getmem(sizeof(node));
	tmp_node->key = key;
	tmp_node->next = NULL;

	if(queue_type->rear == NULL)
		queue_type->rear = queue_type->front = tmp_node;	
	else
		queue_type->rear = (queue_type->rear)->next = tmp_node;	
}

pid32 dequeue_temp(queue *queue_type)
{
	pid32 temp;

	if(queue_type->front == NULL)
	{
		queue_type->rear = NULL;
		printf("queue empty \n");
		return -1;	
	}
	else
	{
		temp = (queue_type->front)->key;
		queue_type->front = (queue_type->front)->next;
		return temp;	
	}	
}

