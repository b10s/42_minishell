#include "./parse.h"

// Q: how do we signal err in parse()? (return NULL or change ctx->some_field)
// A: return NULL
int count_commands(char **cmds);
t_context *parse(char *line)
{
	t_context *ctx;

	ctx = init_ctx();
	if (ctx == NULL)
		return (NULL);
	//printf("line [%s]\n", line);
	//printf("out_red [%s] \n", ctx->out_red);
	// do I need to free commands?
	char **commands;
	commands = ft_split(line, '|');
	if (commands == NULL)
	{
		free_ctx(ctx);
		return (NULL);
	}
	printf("cmd 1st: [%s]\n", commands[0]);
	ctx->commands = commands;
	ctx->cmd_cnt = count_commands(commands);
	//TODO split by spaces, 
	// remove spaces from left and from right
	// remove double spaces
	// count number of commands

	//commands = ft_split(line, '|');
	return ctx;
}

int count_commands(char **cmds)
{
	int cnt;

	cnt = 0;
	while(cmds[cnt] != NULL)
		cnt++;
	return (cnt);
}

// execve("/usr/bin/ls", ["ls", "-lah", NULL], 0x560e91e56530 /* 65 vars */) = 0

// use split to split into '|' pipes e.g.: ls -lah | cat

// Q fail on wrong syntax here or later?

// A It will fail if there is something there should not be, specifically, special characters
// like a '|' followed by a '<' instead of a non-special character.

t_context *init_ctx(t_context *ctx)
{
	ctx = malloc(sizeof(t_context));
	if (ctx == NULL) {
		return NULL;
	}
	ctx->commands = malloc(sizeof(char *));
	if (ctx->commands == NULL)
	{
		free_ctx(ctx);
		return (NULL);
	}
	ctx->commands[0] = NULL;
	ctx->cmd_cnt = 0;
	ctx->out_red = NULL;
	ctx->in_red = NULL;
	ctx->out_append_mode_flg = 0;
	ctx->here_doc_delim = NULL;
	return ctx;
}

void free_ctx(t_context *ctx)
{
	printf("free ctx()\n");
	int i;

	i = 0;
	while(ctx->commands[i] != NULL)
	{
		free(ctx->commands[i]);
		i++;
	}
	free(ctx->commands);
	free(ctx->out_red);
	free(ctx->in_red);
	free(ctx->here_doc_delim);
	free(ctx);
}

void print_ctx(t_context *ctx)
{
	int i;

	i = 0;
	printf("commands are\n");
	while(ctx->commands[i] != NULL)
	{
		printf("cmd #%d: [%s]\n", i, ctx->commands[i]);
		i++;
	}

	printf("there are [%d] commands in line\n", ctx->cmd_cnt);
	
}
