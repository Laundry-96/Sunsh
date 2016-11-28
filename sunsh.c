#include "sunsh.h" 

size_t env_length;
char **env;

int run_sunsh()
{
	/* Declare variables */
	char **command, *full_command;
	pid_t id;
	size_t i, commands;
	
	/* set environment to null */
	env = NULL;
	env_length = 0;

	/* Infinite loop for shell execution */
	while(1)
	{
		/* Get the command the user wants to execute */
		command = get_command(&commands, &full_command);
		
		/* Check for a valid command, and if not, try again */
		if(command == NULL)
			continue;
		
		/* Make sure command isn't a built in shell command */
		else if(built_in(command))
			shell_execute(command, commands, full_command);

		/* Command is a program to be run */
		else
		{
			/* Everything is dandy; execute the statement */
			id = fork();
			if(id == 0)
			{	
				if (execvp(command[0], command) == -1)
				{
					printf("exec error: No such file or directory\n");
				}
			}

			/* Wait for the process to finish */
			wait(NULL);
		}

		for(i = 0; i < commands; i++)
		{
			free(command[i]);
			command[i] = NULL;
		}

		free(command);
		command = NULL;
	}
		
	/* Exit with no errors :) */
		return 0;
}

char **parse_input(char line[], size_t *length)
{
	/* Declare variables */
	size_t i;
	char buffer[LINE_BUFFER], **arr, *token;

	/* Initialize variables */
	/* Initialize get_argument_count + 1 because we must account for trailing null */
	arr = malloc(sizeof(char*) * (get_argument_count(line) + 1));
	i = 0;

	/* Error check */
	if(arr == NULL)
	{
		printf("UNABLE TO ALLOCATE MEMORY!\n EXITING!");
		exit(-1);
	}

	if(sprintf(buffer, line) < 0)
	{
		printf("ERROR! SPRINTF() RETURNED A NEGATIVE VALUE!\n");
		printf("TRY AGAIN!\n");
		return NULL;
	}

	/* Everything is dandy; tokenize the string */
	token = strtok(buffer, " \t\n");

	while(token)
	{
		/* Use strlen(token) + 1 because it doesn't include terminating char */
		arr[i] = malloc((strlen(token) + 1) * sizeof(char));
		strcpy(arr[i], token);
		i++;
		token = strtok(NULL, " \t\n");
	}

	/* Don't forget to set the last argument to NULL for execv()! */
	/* NOTE: We don't malloc here because we are not creating a string */
	/* If anything, we should free(arr[i]), and then call malloc(sizeof(char)) */
	arr[i++] = '\0';
	
	/* Assign length for deallocation */
	*length = i;

	return arr;
}

char **get_command(size_t *commands, char **full_command)
{
	/* Declare variables */
	char input_line[LINE_BUFFER];

	/* Print the shell line and get user input */
	printf("SUNSH> ");

	/* Error check */
	if(fgets(input_line, LINE_BUFFER, stdin) == 0)
	{
		printf("ERROR ON LINE PARSING!\n TRY AGAIN!\n");
		return NULL;
	}

	/* Return the full command */
	*full_command = input_line;

	/* Return the parsed input */
	return parse_input(input_line, commands);
}

size_t get_argument_count(char line[])
{
	size_t counter, i;

	counter = 0;
	
	for(i = 0; line[i] != '\0'; i++)
	{
		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		{
			counter++; 
			i++; 
		}
		
		while(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
	}
	
	return counter;
}

int built_in(char **command)
{
	if(command == NULL)
		return 0;
	else if(strcmp(*command, "cd") == 0)
		return 1;
	else if(strcmp(*command, "exit") == 0)
		return 1;
	else if(strcmp(*command, "chdir") == 0)
		return 1;
	else if(strcmp(*command, "getenv") == 0)
		return 1;
	else if(strcmp(*command, "setenv") == 0)
		return 1;
	else if(strcmp(*command, "echo") == 0)
		return 1;
	else
		return 0;
}

void shell_execute(char **command, size_t args, char *full_command)
{
	/* Change directory */
	if(strcmp(*command, "cd") == 0 || strcmp(*command, "chdir") == 0)
		printf("chdir not implemented\n");

	/* Exit */
	else if(strcmp(*command, "exit") == 0)
	{
		/* If there are more than two + NULL arguments */
		if(3 < args)
			printf("Invalid arguments for exit... Ignoring...\n");
		
		/* Make sure second argument is valid */
		else if(args == 3)
		{
			long num_to_return;
			char *next;

			num_to_return = strtol(command[1], &next, 10);
			
			/* No invalid characters */
			if(*next == '\0')
				exit(num_to_return);

			/* Read invalid characers */
			else
			{
				printf("Invalid arg to exit... Ignoring...\n");
			}
		}

		else
			exit(0);
	}

	/* Getenv */
	else if(strcmp(*command, "getenv") == 0)
	{
		size_t i;

		/* Make sure we have an environment variable to get */
		if(args != 3)
			printf("Invalid number of arguments. Only one argument accepted\n");

		/* NULL check */
		if(env_length != 0)
		{
			for(i = 0; i < env_length; i+=2)
			{
				if(strcmp(command[1], env[i]) == 0)
				{
					printf("%s", env[i+1]);
					break;
				}
			}
		}

		printf("\n");
	}

	/* Setenv */
	else if(strcmp(*command, "setenv") == 0)
	{
		printf("%s\n", full_command);
	}
}
