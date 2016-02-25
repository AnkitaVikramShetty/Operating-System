#ifndef _QUEUE_TEMP_H_
#define _QUEUE_TEMP_H_	120 //give it a value like 120??

extern int count_shared;

typedef struct Node
{
	pid32 key;
	struct Node *next;
} node;

typedef struct queue_entry {
	node *front;
	node *rear;
} queue;

/* Interface for system call */
void enqueue_temp(pid32, queue*);
pid32 dequeue_temp(queue*);

#endif /* _QUEUE_TEMP_H_ */
