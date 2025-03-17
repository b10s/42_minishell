#include "./parse.h"

// Q: how do we signal err in parse()? (return NULL or change ctx->some_field)
// A: return NULL
int count_commands(char **cmds);
t_context *parse(char *line)
{
	char **commands;
	char	*tmp;
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
	ctx->cmd_cnt = count_commands(commands);ctx = init_ctx();
	if (ctx == NULL)
		return (NULL);

	printf("single quotes cnt [%d]\n", count_single_quotes(line));
	printf("double quotes cnt [%d]\n", count_double_quotes(line));
	// non fatal err: unclosed braces - try new line
	if (validate_quotes(line) != 0)
	{
		ctx->err = malloc(ft_strlen(QUOTES_ERR));
		if (ctx->err == NULL)
			return (NULL);
		ctx->err = QUOTES_ERR;
		return (ctx);
	}

	printf("[%s] <- line before rm spaces\n", line);

	// remove spaces inside
	// TODO: check all old buffers are freed
	// and if returned NULL then err is propogated
	tmp = rm_multi_spaces(line);
	free(line);
	line = tmp;
	if (line == NULL)
		return (NULL);
	printf("[%s] <- line after rm spaces in mid\n", line);

	// remove spaces before and after, trim
	tmp = ft_strtrim(line, " ");
	free(line);
	line = tmp;
	if (line == NULL)
		return (NULL);
	printf("[%s] <- line after rm spaces on sides\n", line);


	// TODO: rm spaces from left and right
	// TODO: split, then again use trim to remove spaces
	// TODO: do my own split which ignores | in quotes ' or "
	commands = split_pipes(line);
	if (commands == NULL)
	{
		free_ctx(ctx);
		return (NULL);
	}
	ctx->cmd_cnt = count_commands(commands);

	// trim after splitting once again since it might be 'echo "a" | wc'
	// space before and after |
	//int i = 0;

	ctx->cmds = malloc(ctx->cmd_cnt * sizeof(t_cmd *));

	// TODO: rm meaningless multi-spaces
	// TODO: do interpolation
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

char **split_pipes(char *str)
{
	int	cmd_cnt;
	char	**cmds;
	char	**ptr;
	int	cmd_len;

	cmds = NULL;
	if (str == NULL)
		return (NULL);
	cmd_cnt = count_pipes(str);
	cmds = malloc(sizeof(char *) * (cmd_cnt+1));
	if (cmds == NULL)
		return (NULL);
	ptr = cmds;
	printf("pipes cnt is [%d]\n", cmd_cnt);


	cmd_len = cmd_size_till_pipe(str);
	while (cmd_len != 0)
	{
		printf("cmd len [%d]\n", cmd_len);
		// TODO: test what substr returns in case 0, 0
		//		empty string or NULL? e.g. `a|b|` 
		*cmds = ft_substr(str, 0, cmd_len);
		if(*cmds == NULL)
		{
			//TODO: free all previous cmds
			return (NULL);
		}
		printf("cmd is [%s]\n", *cmds);
		//TODO trim it here once more
		cmds++;
		str = str + cmd_len;
		if (*str == '|')
			str++;
		cmd_len = cmd_size_till_pipe(str);
	}
	*cmds = NULL;
	return (ptr);
}

int cmd_size_till_pipe(char *cmd)
{
	int len;
	short qq;
	short qw;

	qq = 0;
	qw = 0;

	len = 0;
	while (*cmd != '\0')
	{
		if (*cmd == '\"' && qq == 0)
			qw = qw ^ 1;
		if (*cmd == '\'' && qw == 0)
			qq = qq ^ 1;

		if (*cmd == '|' && qw == 0 && qq == 0)
			break;
		len++;
		cmd++;
	}

	return (len);
}

int count_pipes(char *str)
{
	short qq;
	short qw;
	int	cnt;

	qq = 0;
	qw = 0;
	cnt = 0;
	while (*str != '\0')
	{
		if (*str == '\"' && qq == 0)
			qw = qw ^ 1;
		if (*str == '\'' && qw == 0)
			qq = qq ^ 1;
		if (*str == '|' && qw == 0 && qq == 0)
			cnt++;
		str++;
	}
	return (cnt);
}

//int count_commands(char **cmds)
//{
//	int i = 0;

	//ctx->cmds = malloc(ctx->cmd_cnt * sizeof(t_cmd *));
//	while( i < ctx->cmd_cnt)
//	{
//		ctx->cmds[i] = ft_split(commands[i], ' ');
//		i++;
//	}

	//TODO split by spaces, 
	// remove spaces from left and from right
	// remove double spaces

	//commands = ft_split(line, '|');
//	return ctx;
//}

int count_commands(char **cmds)
{
	int cnt;

	cnt = 0;
	while(cmds[cnt] != NULL)
		cnt++;
	return (cnt);
}

int count_single_quotes(char *str)
{
	int	res;
	short	qw;
	short	qq;

	res = 0;
	qw = 0;
	qq = 0;
	while(*str != '\0')
	{
		if (*str == '\"' && qq == 0)
			qw = qw ^ 1; 
		if (*str == '\'' && qw == 0)
			qq = qq ^ 1; 
		if (*str == '\'' && qw == 0)
			res++;
		str++;
	}
	return (res);
}

int count_double_quotes(char *str)
{
	int	res;
	short	qw;
	short	qq;

	res = 0;
	qw = 0;
	qq = 0;
	while(*str != '\0')
	{
		if (*str == '\'' && qq == 0)
			qw = qw ^ 1; 
		if (*str == '\"' && qw == 0)
			qq = qq ^ 1; 
		if (*str == '\"' && qw == 0)
			res++;
		str++;
	}
	return (res);
}

int validate_quotes(char *str)
{
	if (count_single_quotes(str) % 2 != 0)
		return (1);
	if (count_double_quotes(str) % 2 != 0)
		return (1);
	return (0);
}

// do not remove spaces in ' hey ' and in " hi "
char *rm_multi_spaces(char *str) {
	size_t	spaces_to_rm;
	size_t	str_len;
	char	*new_str;
	char *tmp;
	short qw;
	short qq;
	short sp;

	qq = 0;
	qw = 0;
	sp = 0;
	spaces_to_rm = count_spaces_to_rm(str);
	str_len = ft_strlen(str);
	printf("spaces to rm [%ld]\n", spaces_to_rm);
	new_str = malloc(str_len - spaces_to_rm + 1);
	if (new_str == NULL)
		return (NULL);

	tmp = new_str;
	while(*str != '\0')
	{
		if (*str == '\'' && qq == 0)
			qw = qw ^ 1; 
		if (*str == '\"' && qw == 0)
			qq = qq ^ 1; 

		if (*str == ' ' && qq == 0 && qw == 0)
		{
			if (sp != 1)
			{
				*tmp = *str;
				tmp++;
				str++;
			}
			else
				str++;
			sp = 1;
		} else
		{
			sp = 0;
			*tmp = *str;
			str++;
			tmp++;
		}
	}
	*tmp = '\0';
	return (new_str);
}

// if it is very first and very last space(s) - rm as well

// write trim and rtrim
size_t count_spaces_to_rm(char *str)
{
	size_t cnt;
	short qq;
	short qw;
	short sp;

	cnt = 0;
	qq = 0;
	qw = 0;
	sp = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && qq == 0)
			qw = qw ^ 1; 
		if (*str == '\"' && qw == 0)
			qq = qq ^ 1; 
		if (*str == ' ' && qq == 0 && qw == 0)
		{
			if (sp == 1)
				cnt++;
			sp = 1;
		} else
			sp = 0;
		str++;
	}

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

	ctx->cmds = malloc(sizeof(t_cmd *));
	if (ctx->cmds == NULL)
	{
		free_ctx(ctx);
		return (NULL);
	}
	ctx->cmds[0] = NULL;
	ctx->cmd_cnt = 0;
	ctx->err = NULL;
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
               //printf("cmd #%d: [%s]\n", i, ctx->cmds[i][0]);
               //int j = 1;
               //while(ctx->cmds[i][j] != NULL)
               //{
                       //printf("\targ #%d: [%s]\n", j, ctx->cmds[i][j]);
                //       j++;
               //}
               i++;
       }
      // printf("there are [%d] commands in line\n", ctx->cmd_cnt);  
}
