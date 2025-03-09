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

