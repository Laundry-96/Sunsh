#include "sunsh.h"

int run_sunsh()
{       
	while(1)
	{
		char line[LINE_BUFFER];
        	printf("SUNSH> ");
        	fgets(line, LINE_BUFFER, stdin);
		size_t length;
		char **test = parse_input(line, &length);
        	/* TODO: RUN THE COMMAND */
		int i;
		for(i = 0; i < length; i++)
		{
			printf("%s\n", test[i]);
		}		 

	}
	
        return 0;
}

char **parse_input(char line[], size_t *length)
{
	size_t counter = 0, i;
	for(i = 0; line[i] != '\0'; i++)
	{
		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			{ counter++; i++; }

		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
	}

	char buffer[LINE_BUFFER];	
	printf("%d\n", sizeof(char*) * counter);
	char **arr = malloc(sizeof(char*) * counter);
	int rv = sprintf(buffer, line);
	char *token = strtok(buffer, " \t\n");
	i = 0;
	while(token)
	{
		arr[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	*length = counter;
	return arr;
	/*
        for(i = 0; line[i] != '\0'; i++)
	{
		if(line[i] == ' ' || line[i] == '\n')
		{
			counter++;
		}

		while(line[i] == ' ' || line[i] == '\n')
		{
			i++;
		}
	}

	char *strings[] = malloc(sizeof(*char) * counter);

	for(int i = 0; line[i] != '\0'; i++)
	{
		counter
	}*/
}
