#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
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
	
void splice(char **input_arr, size_t input_length, char ***command, char ****args);

