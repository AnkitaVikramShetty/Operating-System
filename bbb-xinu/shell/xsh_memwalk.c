#include <prodcons.h>

shellcmd xsh_memwalk(int nargs, char *args[]) {

	struct memblk* memptr;
	memptr = memlist.mnext;

	/* For argument '--help', emit help about the 'cat' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) 
	{
		printf("Use: %s \n\n", args[0]);
		printf("Description:\n");
		printf("\t memwalk command in Xinu\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}
	else if(nargs > 1)
	{
		printf("Memwalk takes no arguements\n");
		return 0;
	}
	else	/* Printing addresses & lengths of the free blocks in memory */
	{
		while(memptr != NULL)
		{
			printf("Address of block  : %d\n",memptr);
			printf("Length of block  : %d\n\n",memptr->mlength);
			memptr = memptr->mnext;
		}
	}
	return 0;
}
