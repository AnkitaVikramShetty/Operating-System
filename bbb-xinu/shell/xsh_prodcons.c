#include <prodcons.h>

int n, count_shared;                 		  
//Definition for global variable 'n'. Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce
sid32 consumed, produced;         //Defination for semaphores

int check_integer(char *str)
{
    int i=0;
    for(i=0;i<strlen(str);i++)
        if(!isdigit(str[i]))
            return 0;
    return 1;
}

shellcmd xsh_prodcons(int nargs, char *args[])
{
	//Argument verifications and validations
	int i=0;
	int count = 2000;             //local varible to hold count

	/*Initialise semaphores*/
	consumed = semcreate(1);      
	produced = semcreate(0);
	
	//help
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
	{
		printf("Usage: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tCommand to run producer consumer program\n");
		printf("Options :\n");
		printf("\tprodcons \tproducer produces 2000 values\n");
		printf("\tprodcons 'n' \tproducer produces 'n' values where 'n' is an integer.\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}
	
	if (nargs == 2 && strncmp(args[1], "-f", 7) == 0)
	{
		/*future *f1, *f2, *f3;
		f1 = future_alloc(FUTURE_EXCLUSIVE);
		f2 = future_alloc(FUTURE_EXCLUSIVE);
		f3 = future_alloc(FUTURE_EXCLUSIVE);
	 
		resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
		resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
		resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
		resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
		resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
		resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );
		*/
		
		future *f_exclusive, *f_shared, *f_queue;
 
		f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
		f_shared = future_alloc(FUTURE_SHARED);
		f_queue = future_alloc(FUTURE_QUEUE);

		// Test FUTURE_EXCLUSIVE
		//printf("FOR FUTURE_EXCLUSIVE\n");
		resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
		resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );

		// Test FUTURE_SHARED
		//printf("FOR FUTURE_SHARED\n");
		count_shared = 0;
		resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
		resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
		resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
		resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
		resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );
		
		// Test FUTURE_QUEUE
		//printf("FOR FUTURE_QUEUE\n");
		resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
		resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
		resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
		resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );	
		resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
	}
	/* Implementing network connectivity using futures */
	else if (nargs == 2 && strncmp(args[1], "-n", 7) == 0)
	{		
		future *f_exclusive;
		f_exclusive = future_alloc(FUTURE_EXCLUSIVE);

		// Test FUTURE_EXCLUSIVE
		resume( create(network_cons, 1024, 20, "fcons1", 1, f_exclusive) );
		resume( create(network_prod, 1024, 20, "fprod1", 1, f_exclusive) );
	}
	else
	{
		//Argument verifications and validations
		if(nargs == 2)
		{
			int check = check_integer(args[1]);
			if(check==1)                	 //check args[1]
			    count=atoi(args[1]);         //if present assign value to count
			else
			{
			    printf("Value entered is not valid! Please enter a positive integer value\n");
			    return 0;
			}
		}
		else if (nargs > 2)
		{
			printf("Too many arguments. Prodcons takes a single argument. \n");
			return 0;
		}
		else
			count = 2000;

		//create the process producer and consumer and put them in ready queue.
		//Look at the definations of function create and resume in exinu/system folder for reference.      
		resume( create(producer, 1024, 20, "producer", 1, count) );
		resume( create(consumer, 1024, 20, "consumer", 1, count) );
	}
	return 1;
}
