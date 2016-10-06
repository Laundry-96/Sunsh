#include "sunsh.h" 
int run_sunsh()
{
	/* Declare variables */
	char **command;
	pid_t id;
	size_t i, commands;

	/* Infinite loop for shell execution */
	while(1)
	{
		/* Get the command the user wants to execute */
		command = get_command(&commands);
		
		/* Check for a valid command, and if not, try again */
		if(command == NULL)
			continue;
		
		/* Everything is dandy; execute the statement */
		id = fork();
		if(id == 0)
		{	
			if (execv(command[0], command) == -1)
			{
				printf("exec error: No such file or directory\n");
			}
		}

		/* Wait for the process to finish */
		wait(NULL);
		
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
	int rv;
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
	arr[i] = malloc(sizeof(char));
	arr[i++] = '\0';
	
	/* Assign length for deallocation */
	*length = i;

	return arr;
}

char **get_command(size_t *commands)
{
	/* Declare variables */
	char input_line[LINE_BUFFER];
	size_t length;
	int fgets_return;

	/* Print the shell line and get user input */
	printf("SUNSH> ");

	/* Error check */
	if(fgets(input_line, LINE_BUFFER, stdin) == 0)
	{
		printf("ERROR ON LINE PARSING!\n TRY AGAIN!\n");
		return NULL;
	}

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
