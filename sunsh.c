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
		printf("&command = %p\n", &command);	
		splice(test, length, &command, &args);
		printf("The command is: %s\n", *command);
		
		id = fork();
		if(id == 0)
		{	
			execv(*command, *args);
		}
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

	arr = malloc(sizeof(char*) * counter);
	rv = sprintf(buffer, line);
	token = strtok(buffer, " \t\n");
	i = 0;
	while(token)
	{
		arr[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	*length = i;
	return arr;
}
