#include <lowmem.h>

void testprocess(int count)
{
	int i,addr;
	for(i=1; i<=5; i++)
	{
		addr = (int*)getmem(sizeof(int)); 
	}
	//printf("Fact is %d\n",fact(count));  /* Can run a recursive function */
	killmod(currpid);
}
/* EXTRA : Can use this function to use up stack space */
int fact(int count)
{
	if(count==0 || count==1)
		return 1;
	else
		return count*fact(count-1);	
}
