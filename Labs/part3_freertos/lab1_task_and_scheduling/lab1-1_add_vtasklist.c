/* Buffer to extract trace information */
static char buffer[40*8];

...

	/* Print task list */
	vTaskList(buffer);
	printf("--------------------------------------------------------\n");
	printf("task\t\tstate\tprio\tstack\ttsk id\tcore id\n");
	printf("--------------------------------------------------------\n");
	printf(buffer);
	