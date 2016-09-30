#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sunsh.h"

int main()
{
	return run_sunsh();
	char *line; 
	line = malloc(sizeof(char) * 10);
	printf("SUNSH> ");
	fgets(line, 10, stdin);
		
	/* TODO: RUN THE COMMAND */
	int i;

	for(i = 0; i < 10; i++)
	{
		printf("%d\n", line[i]);
	}
	free(line);

	return 0;
}


