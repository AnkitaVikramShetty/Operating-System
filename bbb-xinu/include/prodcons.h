#include <xinu.h>
#include <stddef.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
#include <queue_temp.h>
#include <future.h>

/*Global variable for producer consumer*/
extern int n; /*this is just declaration*/

/* Declare the required semaphores */
extern sid32 consumed, produced;

/*function Prototype*/
void consumer(int count);
void producer(int count);

int future_prod(future *f);
int future_cons(future *f);

int network_prod(future *f);
int network_cons(future *f);




