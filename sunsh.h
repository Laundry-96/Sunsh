#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define LINE_BUFFER 2048

/*
 * parse_input(char line[])
 * char line[] is a string with max 2048 characters
 * return: Takes the line, and splits it by the spaces.
 */
char **parse_input(char line[], size_t *length);

/*
 * run_sunsh()
 * Starts SUN SHELL
 */
int run_sunsh();

/*
 * get_command(size_t *commands)
 * return: asks for user input, and splits it upon encountering white space
 */
char **get_command(size_t *commands);

/*
 * get_argument_count(char line[])
 * returns: the amount of arguments the user put in
 */
size_t get_argument_count(char line[]);

/*
 * built_in(char** command)
 * returns an int if command is a built in shell command
 * 1 if true, 0 if false
 */
int built_in(char** command);
