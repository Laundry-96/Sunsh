CXX := -Wall -ansi -Wextra -pedantic
all:
	gcc $(CXX) sunsh.c shell_main.c -g -o sunsh
