/*  main.c  - main */
// This is user land

#include <xinu.h>

process	main(void)
{
	/* Run the Xinu shell */
	recvclr();
	resume(create(shell, 4096, 50, "shell", 1, 0));
	
	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		//kprintf("Entering sleep");
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}
