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
		printf("&command = %p\n", &command);
		printf("The command is: %s\n", command);
		
		id = fork();
		if(id == 0)
		{	
			execv(*command, *args[0]);
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

void splice(char **input_arr, size_t input_length, char ***command, char ****args)
{
	size_t i;

	if(input_length == 0)
	{	command = NULL;
		args = NULL;
		return;
	}
	*command = malloc(sizeof(char**));
	*args = malloc(sizeof(char***));
	
	**command = malloc(strlen(input_arr[0]) * sizeof(char));
	**args = malloc(input_length * sizeof(char*));

	strcpy(**command, input_arr[0]);
	printf("input_arr[0] = %s\ncommand = %s\n", input_arr[0], **command);
	for(i = 0; i < input_length - 1; i++)
	{
		**args[i] = malloc(strlen(input_arr[i+1]) * sizeof(char));
		strcpy(**args[i], input_arr[i+1]);
	}
	**args[i] = NULL;
	printf("input_arr[0] = %s\ncommand = %s\n", input_arr[0], **command);
/*	*args[i] = "-la";*/
}
