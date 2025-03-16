/*
TODO
	add function to free context struct on exit
	free line returned by readline
	setup tests for our shel
		include mem leak testing
		go over all tests from eval page
*/

/* Q
	how -l option works in gcc?
	why I can't put -lreadline just after gcc but need to put it at last?
*/


/*
	cd libft
	make
	cd ..

	gcc -Wall -Wextra -Werror main_andrei.c parse/parse.c libft/libft.a environ_functions/free_envs.c -lreadline && ./a.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "./parse/parse.h"

// TODO do we need to use argc, argv?
// Q: why gcc wanrs on unused params argc, argv? any potential pitfalls?
int main() {
	t_context *ctx;
	char *line;

	while(true) {
		//TODO: check what readline can return: NULL, empty string, Crl-D, Crl-C, etc
		line = readline("c001 she11> ");
		//line = interpolate(line,);
		printf("line from readline [%s]\n", line);
		if (line == NULL) 
			break;
		else
		{
			ctx = parse(line);
			if ( ctx == NULL) {
				// TODO unify error message and exit
				printf("fatal ERR\n");
				return (1);
			}
			//print_ctx(ctx);

			// TODO check that parsed ok
			// TODO do operations on parsed line
			free_ctx(ctx);
		}
	}

	//printf("argc [%d], argv addr [%p]\n", argc, argv);
	//printf("line [%s]\n", line);


	// inf loop until EOF?
	/*
	man readline
	...
	RETURN VALUE
  	readline returns the text of the line read. A blank line returns the empty string.
		If EOF is encountered while reading a line, and the line is empty, NULL is returned.
		If an EOF is  read  with  a non-empty line, it is treated as a newline.
	*/
	
	//if (res != 0) {
		//ERR
		//Q do we need to exit or just print some err msg?
		//err();
	//	printf("ERR parsing\n");
	//}
	// here work with context: exec commands
	return (0);
}

