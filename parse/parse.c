#include "./parse.h"

// Q: how do we signal err in parse()? (return NULL or change ctx->some_field)

t_context *parse(char *line, t_context *ctx)
{
	//printf("line [%s]\n", line);
	//printf("out_red [%s] \n", ctx->out_red);
	// do I need to free commands?
	char **commands;
	commands = ft_split(line, '|');
	printf("cmd 1st: [%s]\n", commands[0]);
	//TODO split by spaces, 
	// remove spaces from left and from right
	// remove double spaces
	// count number of commands

	//commands = ft_split(line, '|');
	return ctx;
}

// execve("/usr/bin/ls", ["ls", "-lah", NULL], 0x560e91e56530 /* 65 vars */) = 0

// use split to split into '|' pipes e.g.: ls -lah | cat

// Q fail on wrong syntax here or later?

