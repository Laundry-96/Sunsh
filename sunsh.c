#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 2048

int main()
{
	char line[2048];
	while(strcmp(line, "exit\n") != 0)
	{
		printf("SUNSH> ");
		fgets(line, LINE_BUFFER, stdin);
		
		/* TODO: RUN THE COMMAND */
			
	}

	return 0;
}
