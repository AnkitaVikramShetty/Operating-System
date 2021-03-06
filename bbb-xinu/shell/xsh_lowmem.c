#include <lowmem.h>

char* stack_pointer;
int check;
int stacksize;
	
shellcmd xsh_lowmem(int nargs, char *args[]) {
	int count = 5;	
	char *j;
	int i;
	int trackStack = 0;
	pid32 procid;

	/* For argument '--help', emit help about the 'cat' command	*/
	struct memblk* memptr;
	memptr = memlist.mnext;
	
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) 
	{
		printf("Use: %s \n\n", args[0]);
		printf("Description:\n");
		printf("\t lowmem command in Xinu\n");
		printf("Options :\n");
		printf("\tlowmem -s \t: code for question 9.4\n");
		printf("\tlowmem -m \t: code for question 9.7\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}
	else if (nargs == 2 && strncmp(args[1], "-s", 7) == 0)
	{
		while(memptr != NULL) /* Displays address & length of free block before allocation */
		{
			printf("Address of free block before any allocation : %d\n",memptr);
			printf("Length of free block before any allocation : %d\n\n",memptr->mlength);
			memptr = memptr->mnext;
		}

		check = 0;
		resume(createmod(testprocess, 1024, 20, "testprocess", 1, count));
		sleep(3);
		memptr = memlist.mnext;
		while(memptr != NULL) /* Displays address & length of free block after a part of it is allocated */
		{
			printf("\nAddress of free block after allocating heap/stack for a process : %d\n",memptr);
			printf("Length of free block after allocating heap/stack for a process : %d\n\n",memptr->mlength);
			memptr = memptr->mnext;
		}	
		return 0;	
	}
	else if (nargs == 2 && strncmp(args[1], "-m", 7) == 0)
	{
		while(memptr != NULL) /* Displays address & length of free block before allocation */
		{
			printf("Address of free block before any allocation : %d\n",memptr);
			printf("Length of free block before any allocation : %d\n\n",memptr->mlength);
			memptr = memptr->mnext;
		}

		check = 1;
		procid = createmod(testprocess, 1024, 20, "testprocess", 1, count);
		stack_pointer = proctab[procid].prstkptr; 
		j = stack_pointer; 
		stacksize = proctab[procid].prstklen;

		for(i = 0; i <= stacksize; i++) /* Writes a character into the stack allocated to procid */
		{
			*j = 'b';
			j = j - 1;
		} 
		resume(procid);
		sleep(3); 
		memptr = memlist.mnext;
		while(memptr != NULL) /* Displays address & length of free block after a part of it is allocated */
		{
			printf("\nAddress of free block after allocating heap/stack for a process : %d\n",memptr);
			printf("Length of free block after allocating heap/stack for a process : %d\n\n",memptr->mlength);
			memptr = memptr->mnext;
		}
		return 0;	
	}
	else if(nargs > 1)
	{
		printf("Please use -s or -m as arguments\n");
		return 0;
	}
	return 0;
}
