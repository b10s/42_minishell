#include "./parse.h"

// Q: how do we signal err in parse()? (return NULL or change ctx->some_field)
// A: return NULL
int count_commands(char **cmds);
t_context *parse(char *line)
{
	char **commands;
	t_context *ctx;

	ctx = init_ctx();
	if (ctx == NULL)
		return (NULL);
	commands = ft_split(line, '|');
	if (commands == NULL)
	{
		free_ctx(ctx);
		return (NULL);
	}
	ctx->cmd_cnt = count_commands(commands);
	//int i = 0;

	ctx->cmds = malloc(ctx->cmd_cnt * sizeof(t_cmd *));

	// TODO: rm meaningless multi-spaces
	// TODO: we do interpolation
	// TODO: parse for redirections
	// TODO: split for spaces to be ready to pass to execve

	//while( i < ctx->cmd_cnt)
	//{
	//	ctx->cmds[i] = ft_split(commands[i], ' ');
	//	i++;
	//}

	//TODO split by spaces, 
	// remove spaces from left and from right
	// remove double spaces

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

char *ft_rm_multi_spaces(char *str) {
	size_t	spaces_to_rm;
	size_t	str_len;
	char	*new_str;

	spaces_to_rm = 0;
	str_len = ft_strlen(str);

	new_str = malloc(str_len - spaces_to_rm);

	return (new_str);
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

	ctx->cmds = malloc(sizeof(t_cmd *));
	if (ctx->cmds == NULL)
	{
		free_ctx(ctx);
		return (NULL);
	}
	ctx->cmds[0] = NULL;
	ctx->cmd_cnt = 0;
	//ctx->out_red = NULL;
	//ctx->in_red = NULL;
	//ctx->out_append_mode_flg = 0;
	//ctx->here_doc_delim = NULL;
	return ctx;
}

void free_ctx(t_context *ctx)
{
	printf("free ctx()\n");
	int i;

	i = 0;
	while(ctx->cmds[i] != NULL)
	{
		//free_split(ctx->cmds[i]);
		i++;
	}
	free(ctx->cmds);
	//free(ctx->out_red);
	//free(ctx->in_red);
	//free(ctx->here_doc_delim);
	free(ctx);
}

void print_ctx(t_context *ctx)
{
	int i;

	i = 0;
	printf("commands are\n");
	while(ctx->cmds[i] != NULL)
	{
		printf("cmd #%d: [%s]\n", i, ctx->cmds[i][0]);
		int j = 1;
		while(ctx->cmds[i][j] != NULL)
		{
			printf("\targ #%d: [%s]\n", j, ctx->cmds[i][j]);
			j++;
		}
		i++;
	}

	printf("there are [%d] commands in line\n", ctx->cmd_cnt);
	
}
