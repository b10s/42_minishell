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
	gcc -Wall -Wextra -Werror main_andrei.c parse/parse.c -lreadline && ./a.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "./parse/parse.h"


int main(int argc, char **argv) {
	char *line;
	int	res;
	t_context *ctx;

	line = readline("yo> ");
	printf("argc [%d], argv addr [%p]\n", argc, argv);
	printf("line [%s]\n", line);

	ctx = init_ctx();
	if ( ctx == NULL) {
		printf("fatal ERR\n");
	}
	// inf loop until EOF?
	res = parse(line, ctx);
	if (res != 0) {
		//ERR
		//Q do we need to exit or just print some err msg?
		//err();
		printf("ERR parsing\n");
	}
	// here work with context: exec commands
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

