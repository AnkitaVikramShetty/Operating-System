
#include <xinu.h>
#include <string.h>
#include <stdio.h>

shellcmd xsh_hello(int nargs, char *args[]) {

	/* For argument '--help', emit help about the 'cat' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s \n\n", args[0]);
		printf("Description:\n");
		printf("\t hello command in Xinu\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}
	else if (nargs == 2) 
		printf("Hello %s, Welcome to the world of Xinu\n", args[1]);
	else if(nargs < 2)
		printf("Too less arguements\n");
	else
		printf("Too many arguements\n");
}
