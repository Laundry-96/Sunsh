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
	/* Used to check if setenv command. Special things need to be done for this. */
	int first_run;

	/* Initialize variables */
	/* Initialize get_argument_count + 1 because we must account for trailing null */
	/* IF SETENV RETURN 2 */
	arr = malloc(sizeof(char*) * (get_argument_count(line) + 1));
	i = 0;
	first_run = 1;

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

	for(i = 0; buffer[i] != EOF

	/* REMOVING STRTOK TO PARSE BY HAND */
	/* Everything is dandy; tokenize the string */
	/* token = strtok(buffer, " \t\n");*/
	
	while(false)
	{
		/* Use strlen(token) + 1 because it doesn't include terminating char */
		arr[i] = malloc((strlen(token) + 1) * sizeof(char));
		strcpy(arr[i], token);
		i++;

		/* If this is our first run */
		if(first_run)
		{
			/* Check if we want to use setenv */
			if(strcmp(arr[0], "setenv") == 0)
			{
				/* Parse the rest of the string as one string for putenv */
				token = strtok(NULL, "\0");
				arr[i] = malloc(strlen(token + 1) * sizeof(char));
				strcpy(arr[i], token);
				i++;
				
				/* Set the last argument to NULL */
				arr[i++] = '\0';

				/* Assign length for deallocation */
				*length = i;

				/* Return the array */
				return arr;
			}

			/* Set first run to false */
			first_run = 0;
		}

		token = strtok(NULL, " \t\n");
	}
	/* REMOVING STRTOK TO PARSE BY HAND */

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
	char* first_command;
	int first_command_found;

	counter = 0;
	first_command_found = 0;

	/* "setenv" is 6 characters long and that's all we need */
	first_command = malloc(sizeof(char) * 6); 
	if(first_command == NULL)
		return 0;

	/* Set first_command to all null chars */
	for(i = 0; i < 6; i++)
		first_command[i] = '\0';

	for(i = 0; line[i] != '\0'; i++)
	{
		/* If we have found the first command */
		if(!first_command_found)
		{
			/* While we are going through whitespace */
			while((line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
				i++;

			/* If there is no character after the whitespace */
			if(line[i] == '\0')
				return 0;

			/* While there are characters to read, and we have yet to read 6 characters */
			while(line[i] != '\0' && first_command_found < 6)
			{
				first_command[first_command_found++] = line[i++];
			}	

			/* If it's setenv, we need 3 parameters, 1 for setenv, 2 for rest of string, 3 for null */
			if(strcmp(first_command, "setenv") == 0)
				return 3;
		}

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
		printf("%s\n", command[1]);
	}
}
