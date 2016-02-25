/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <queue.h>

/* Semaphore state definitions */
#define SFREE 0x01 
#define SUSED 0x02 
/* type definition of "semaphore" */
typedef unsigned int semaphore;

struct sement                   /* semaphore table entry      */
{
    char state;                 
    int count;                  
    qid_typ queue;              
};

extern struct sement semtab[];

/* isbadsem - check validity of reqested semaphore id and state */
#define isbadsem(s) ((s >= NSEM) || (SFREE == semtab[s].state))

/* Semaphore function prototypes */
syscall wait(semaphore);
syscall signal(semaphore);
syscall signaln(semaphore, int);
semaphore semcreate(int);
syscall semfree(semaphore);
syscall semcount(semaphore);

#endif                          /* _SEMAPHORE_H */
