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

	gcc -Wall -Wextra -Werror main_andrei.c parse/parse.c libft/libft.a -lreadline && ./a.out
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

	ctx = init_ctx();
	if ( ctx == NULL) {
		// TODO unify error message and exit
		printf("fatal ERR\n");
		return (1);
	}

	while(true) {
		//TODO: check what readline can return: NULL, empty string, Crl-D, Crl-C, etc
		line = readline("c001 she11> ");
		printf("line from readline [%s]\n", line);
		if (line == NULL) 
		{
			free_ctx(ctx);
			break;
		}
		else
		{
			ctx = parse(line, ctx);
			// TODO check that parsed ok
			// TODO do operations on parsed line
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

t_context *init_ctx(t_context *ctx)
{
	ctx = malloc(sizeof(t_context));
	if (ctx == NULL) {
		return NULL;
	}
	ctx->commands = NULL;
	ctx->cmd_cnt = 0;
	ctx->out_red = NULL;
	ctx->in_red = NULL;
	ctx->out_fd = stdout;
	ctx->in_fd = stdin;
	ctx->out_append_mode_flg = 0;
	ctx->here_doc_delim = NULL;
	return ctx;
}

void free_ctx(t_context *ctx)
{
	free(ctx->commands);
	free(ctx->out_red);
	free(ctx->in_red);
	free(ctx->here_doc_delim);
	free(ctx);
}

