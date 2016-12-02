CXX := -Wall
all: sunsh.c sunsh.h shell_main.c utils.c utils.h
	gcc $(CXX) sunsh.c shell_main.c utils.c -g -o sunsh
