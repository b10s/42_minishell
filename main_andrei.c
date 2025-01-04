/*
TODO
	add function to free context struct on exit
*/

/* Q
	how -l option works in gcc?
*/


/*
	gcc -lreadline -Wall -Wextra -Werror main_andrei.c && ./a.out
*/

#include <stdio.h>
#include <readline/readline.h>


int main(int argc, char *argv[])
{
	char *line;
	line = readline("yo> ");
	printf("argc [%d], argv addr [%p]\n", argc, argv);
	printf("line [%s]\n", line);
}
