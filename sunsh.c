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

	printf("Starting out with the pointer cmd: %p and args: %p\n", (void*)command, (void*)args);
	printf("Starting out with the deref cmd: %p and args: %p\n", (void*)*command, (void*)*args);
	size_t i;

	if(input_length == 0)
	{	command = NULL;
		args = NULL;
		return;
	}

	*command = malloc(sizeof(char**));
	*args = malloc(sizeof(char***));
	
	**command = malloc((strlen(input_arr[0]) + 1) * sizeof(char));
	**args = malloc(input_length * sizeof(char*));

	printf("Pointer of command = %p\nPointer of args = %p\n", (void*)**command, (void*)**args);

	strcpy(**command, input_arr[0]);
	printf("input_arr[0] = %s\ncommand = %s\n", input_arr[0], **command);
	for(i = 0; i < input_length - 1; i++)
	{
		**args[i] = malloc((strlen(input_arr[i+1]) + 1) * sizeof(char));
		strcpy(**args[i], input_arr[i+1]);
	}
	**args[i] = NULL;
	printf("input_arr[0] = %s\ncommand = %s\n", input_arr[0], **command);
/*	*args[i] = "-la";*/
}
