#include "sunsh.h" 
int run_sunsh()
{       
	while(1)
	{
		char line[LINE_BUFFER], **test, **command, ***args;
        	size_t length, i;
		pid_t id;
		printf("SUNSH> ");
        	fgets(line, LINE_BUFFER, stdin);
		test = parse_input(line, &length);
		id = fork();
		if(id == 0)
		{	
			execv(test[0], test);
		}
	wait();
	}
	
        return 0;
}

char **parse_input(char line[], size_t *length)
{
	size_t counter = 0, i;
	int rv;
	char buffer[LINE_BUFFER], **arr, *token;
	for(i = 0; line[i] != '\0'; i++)
	{
		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			{ counter++; i++; }

		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
	}

	arr = malloc(sizeof(char*) * (counter + 1));
	rv = sprintf(buffer, line);
	token = strtok(buffer, " \t\n");
	i = 0;
	while(token)
	{
		arr[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	arr[i] = '\0';
	*length = i;
	return arr;
}
