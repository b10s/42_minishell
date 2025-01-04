#include "./parse.h"

int parse(char *line, t_context *ctx)
{
	printf("line [%s]\n", line);
	printf("out_red [%s] \n", ctx->out_red);
	// do I need to free commands?
	char **commands;
	commands = ft_split(line, '|');
	printf("cmd 1st: [%s]\n", commands[0]);
	//TODO split by spaces, 
	// remove spaces from left and from right
	// remove double spaces
	// count number of commands

	//ctx->commands = ft_split(line, '|');
	return 1;
}

// execve("/usr/bin/ls", ["ls", "-lah"], 0x560e91e56530 /* 65 vars */) = 0

// use split to split into '|' pipes e.g.: ls -lah | cat

// Q fail on wrong syntax here or later?

