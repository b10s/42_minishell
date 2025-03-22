/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/03/22 23:40:22 by aenshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

//TODO:
// - return NULL on all critical errors or set ctx->err on non critical
// - check that all allocation are: a) done with calloc b) checked for NULL
// - check there is no printf or prohibited functions with nm

// TODO: check all old buffers are freed
//TODO decide where to to free_ctx(ctx);
	// FIXME: do +1 and use calloc to have NULL at the end at line 64
	// ctx->cmds = malloc(ctx->cmd_cnt * sizeof(t_cmd *)); off by one?

//TODO if there token or not - fatal or just user typo err
	// when we receive token and it is NULL or bad -
	// prob we don't need to exit but set err

//TODO make ctx with err return ctx
	// at wrong redirection line 120 or so

					//TODO return non fatal err in ctx field
						//printf("unknown token [%c]\n", *pos_in_cmd);
						// not NULL
						// line 198 approx
t_context	*parse(char *line, t_minishell *ms)
{
	t_context	*ctx;
	t_token		*tok;
	t_cmd		**cmds;
	t_red		**reds;
	t_red		*red;
	char		*pos_in_cmd;
	char		**commands;
	char		**wrds;
	char		*tmp;
	int			i;
	int			red_cnt;
	int			red_max;
	int			wrd_cnt;
	int			wrd_max;

	red = NULL;
	i = 0;
	red_cnt = 0;
	red_max = 5;
	wrd_cnt = 0;
	wrd_max = 5;
	ctx = init_ctx();
	if (ctx == NULL)
		return (NULL);
	ctx->pipe_read = -1;
	ctx->pipe_read_index = -1;
	if (ctx == NULL)
		return (NULL);
	if (validate_quotes(line) != 0)
	{
		ctx->err = malloc(ft_strlen(QUOTES_ERR));
		if (ctx->err == NULL)
			return (NULL);
		ctx->err = QUOTES_ERR;
		return (ctx);
	}
	tmp = rm_multi_spaces(line);
	free(line);
	line = tmp;
	tmp = rm_spaces_near_redir(line);
	free(line);
	line = tmp;
	if (line == NULL)
		return (NULL);
	tmp = ft_strtrim(line, " ");
	free(line);
	line = tmp;
	if (line == NULL)
		return (NULL);
	commands = split_pipes(line);
	if (commands == NULL)
	{
		return (NULL);
	}
	ctx->cmd_cnt = count_commands(commands);
	ctx->cmds = malloc(ctx->cmd_cnt * sizeof(t_cmd *));
	cmds = malloc(sizeof(t_cmd *) * (ctx->cmd_cnt + 1));
	if (cmds == NULL)
		return (NULL);
	i = -1;
	while (++i < ctx->cmd_cnt + 1)
		cmds[i] = NULL;
	i = 0;
	while (i < ctx->cmd_cnt)
	{
		cmds[i] = malloc(sizeof(t_cmd));
		if (cmds[i] == NULL)
			return (NULL);
		cmds[i]->out_fd = -1;
		cmds[i]->in_fd = -1;
		cmds[i]->here_doc_filename = NULL;
		pos_in_cmd = commands[i];
		wrds = ft_calloc((wrd_max + 1), sizeof(char *));
		reds = ft_calloc((red_max + 1), sizeof(t_red *));
		while (42 == 42)
		{
			if (*pos_in_cmd == ' ')
			{
				pos_in_cmd++;
				continue ;
			}
			free(red);
			red = NULL;
			if (*pos_in_cmd == '>')
			{
				if (pos_in_cmd[1] == '>')
				{
					pos_in_cmd = pos_in_cmd + 2;
					tok = get_next_token(pos_in_cmd);
					if (tok == NULL)
						return (NULL);
					if (tok->len == 0)
						break ;
					pos_in_cmd = pos_in_cmd + tok->len;
					red = malloc(sizeof(t_red *));
					if (red == NULL)
						return (NULL);
					red->type = OUT_APPEND;
					red->fname_or_delim = tok->tok;
				}
				else
				{
					pos_in_cmd = pos_in_cmd + 1;
					tok = get_next_token(pos_in_cmd);
					if (tok == NULL)
						return (NULL);
					if (tok->len == 0)
						break ;
					pos_in_cmd = pos_in_cmd + tok->len;
					red = malloc(sizeof(t_red *));
					if (red == NULL)
						return (NULL);
					red->type = OUT;
					red->fname_or_delim = tok->tok;
				}
			}
			if (red != NULL)
			{
				add_reds(&reds, red, &red_cnt, &red_max);
				continue ;
			}
			if (*pos_in_cmd == '<')
			{
				if (pos_in_cmd[1] == '<')
				{
					pos_in_cmd = pos_in_cmd + 2;
					tok = get_next_token(pos_in_cmd);
					if (tok == NULL)
						return (NULL);
					if (tok->len == 0)
						break ;
					pos_in_cmd = pos_in_cmd + tok->len;
					red = malloc(sizeof(t_red *));
					if (red == NULL)
						return (NULL);
					red->type = HERE_DOC;
					red->fname_or_delim = tok->tok;
				}
				else
				{
					pos_in_cmd = pos_in_cmd + 1;
					tok = get_next_token(pos_in_cmd);
					if (tok == NULL)
						return (NULL);
					if (tok->len == 0)
						break ;
					pos_in_cmd = pos_in_cmd + tok->len;
					red = malloc(sizeof(t_red *));
					if (red == NULL)
						return (NULL);
					red->type = IN;
					red->fname_or_delim = tok->tok;
				}
			}
			if (red != NULL)
			{
				add_reds(&reds, red, &red_cnt, &red_max);
				continue ;
			}
			tok = get_next_token(pos_in_cmd);
			if (tok == NULL)
				return (NULL);
			if (tok->len == 0)
			{
				if (*pos_in_cmd == '\0')
					break ;
				else
					return (NULL);
			}
			add_word(&wrds, tok->tok, &wrd_cnt, &wrd_max);
			pos_in_cmd = pos_in_cmd + tok->len;
			if (*pos_in_cmd == ' ')
				pos_in_cmd++;
		}
		cmds[i]->reds = reds;
		cmds[i]->cmd_with_args = wrds;
		i++;
	}
	ctx->cmds = cmds;
	if (interp_remquotelayer(ctx, ms) == EXIT_FAILURE)
		return (free_ctx(ctx, ms), NULL);
	return (ctx);
}

//TODO check null for calloc
void	add_reds(t_red ***reds, t_red *r, int *red_cnt, int *red_max)
{
	t_red	**new_reds;
	t_red	**reds_ptr;
	int		i;

	i = 0;
	reds_ptr = *reds;
	if (*red_cnt == *red_max)
	{
		*red_max += 5;
		new_reds = ft_calloc((*red_max + 1), sizeof(t_red *));
		while (reds_ptr[i] != NULL)
		{
			new_reds[i] = reds_ptr[i];
			i++;
		}
		free(*reds);
		*reds = new_reds;
		reds_ptr = new_reds;
	}
	i = 0;
	while (reds_ptr[i] != NULL)
		i++;
	reds_ptr[i] = ft_calloc(1, sizeof(t_red *));
	reds_ptr[i]->type = r->type;
	reds_ptr[i]->fname_or_delim = ft_strdup(r->fname_or_delim);
	*red_cnt = *red_cnt + 1;
}

//TODO err handle for NULL for calloc
void	add_word(char ***words, char *w, int *wrd_cnt, int *wrd_max)
{
	char	**new_words;
	char	**words_ptr;
	int		i;

	i = 0;
	words_ptr = *words;
	if (*wrd_cnt == *wrd_max)
	{
		*wrd_max += 5;
		new_words = ft_calloc((*wrd_max + 1), sizeof(char *));
		while (words_ptr[i] != NULL)
		{
			new_words[i] = words_ptr[i];
			i++;
		}
		free(*words);
		*words = new_words;
		words_ptr = new_words;
	}
	i = 0;
	while (words_ptr[i] != NULL)
		i++;
	words_ptr[i] = ft_strdup(w);
	*wrd_cnt = *wrd_cnt + 1;
}

int	token_allowed_chars(char c)
{
	int	res;

	res = 0;
	if (c == ' ')
		return (0);
	if (c == '<' || c == '>')
		return (0);
	if (ft_isalnum(c) == 1)
		res = 1;
	if (c == '_' || c == '.' || c == '-')
		res = 1;
	if (ft_isprint(c) == 1)
		res = 1;
	return (res);
}

// token is contiguos sequence of characters which are
// A-Za-z0-9_ dot . dash - without quotes ' or "
// or all printable ascii inside quotes ' or "
int	get_token_len(char *str)
{
	int		len;
	short	qq;
	short	qw;

	len = 0;
	qq = 0;
	qw = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && qq == 0)
		{
			qw = qw ^ 1;
			len++;
			str++;
			continue ;
		}
		if (*str == '\"' && qw == 0)
		{
			qq = qq ^ 1;
			len++;
			str++;
			continue ;
		}
		if (qw == 1 || qq == 1)
		{
			if (ft_isprint(*str) != 1)
				break ;
		}
		else
		{
			if (token_allowed_chars(*str) != 1)
				break ;
		}
		str++;
		len++;
	}
	return (len);
}


t_token *get_next_token(char *str) {
	t_token *tok;

	//printf("get tok parsin [%s]\n", str);
	tok = malloc(sizeof(t_token));
	if (tok == NULL)
		return (NULL);
	
	tok->beg = str;
	tok->len = get_token_len(str);
	//printf("token len [%d]\n", tok->len);

	tok->tok = NULL;
	if (tok->len == 0)
		return (tok);

	tok->tok = malloc(sizeof(char) * (tok->len + 1));
	if (tok->tok == NULL) {
		//TODO free tok
		return (NULL);
	}
	tok->tok = ft_memcpy(tok->tok, str, tok->len);
	tok->tok[tok->len] = '\0';

	//printf("token len is [%d]\n", tok->len);

	return (tok);
}

size_t count_spaces_to_rm_near_redir(char *str)
{
	size_t cnt;
	short qq;
	short qw;
	char pre = '\0';

	cnt = 0;
	qq = 0;
	qw = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && qq == 0)
			qw = qw ^ 1;
		if (*str == '\"' && qw == 0)
			qq = qq ^ 1;

		if ((*str == '<' || *str == '>') && qq == 0 && qw == 0)
			if (pre == ' ')
				cnt++;
		if (*str == ' ' && qq == 0 && qw == 0)
			if (pre == '<' || pre == '>')
				cnt++;
		pre = *str;
		str++;
	}

	return (cnt);
}

char *rm_spaces_near_redir(char *str)
{
	char *new_str;
	short qq;
	short qw;
	char pre = '\0';
	size_t new_len;
	char *tmp;


	new_len = ft_strlen(str) - count_spaces_to_rm_near_redir(str) + 1;
	//printf("new len [%ld]\n", new_len);
	new_str = malloc(sizeof(char) * new_len);
	if (new_str == NULL)
		return (NULL);
	tmp = new_str;
	qq = 0;
	qw = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && qq == 0)
			qw = qw ^ 1;
		if (*str == '\"' && qw == 0)
			qq = qq ^ 1;

		*new_str = *str;

		if ((*str == '<' || *str == '>') && qq == 0 && qw == 0)
			if (pre == ' ')
			{
				new_str--;
				*new_str = *str;
			}

		if (*str == ' ' && qq == 0 && qw == 0)
			if (pre == '<' || pre == '>')
				new_str--;

		pre = *str;
		str++;
		new_str++;
	}
	*new_str = '\0';

	//printf("returning new string [%s]\n", new_str);
	return (tmp);
}

char **split_pipes(char *str)
{
	int	cmd_cnt;
	char	**cmds;
	char	**ptr;
	char	*tmp;
	int	cmd_len;

	cmds = NULL;
	if (str == NULL)
		return (NULL);
	cmd_cnt = count_pipes(str);
	cmds = malloc(sizeof(char *) * (cmd_cnt+1));
	if (cmds == NULL)
		return (NULL);
	ptr = cmds;
	//printf("pipes cnt is [%d]\n", cmd_cnt);


	cmd_len = cmd_size_till_pipe(str);
	while (cmd_len != 0)
	{
		//printf("cmd len [%d]\n", cmd_len);
		// TODO: test what substr returns in case 0, 0
		//		empty string or NULL? e.g. `a|b|` 
		*cmds = ft_substr(str, 0, cmd_len);

		// remove spaces before and after, trim
		tmp = ft_strtrim(*cmds, " ");
		free(*cmds);
		*cmds = tmp;
		// TODO: make sure to free all cmds malloced before
		if (tmp == NULL)
			return (NULL);

		if(*cmds == NULL)
		{
			//TODO: free all previous cmds
			return (NULL);
		}
		//printf("cmd is [%s]\n", *cmds);
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
	//printf("spaces to rm [%ld]\n", spaces_to_rm);
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

t_context *init_ctx(void)
{
	t_context	*ctx;

	ctx = malloc(sizeof(t_context));
	if (ctx == NULL) {
		return NULL;
	}

	ctx->cmds = malloc(sizeof(t_cmd *));
	if (ctx->cmds == NULL)
	{
		//free_ctx(ctx);
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

/*
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
*/


/*
void print_ctx(t_context *ctx)
{
       int i;
       i = 0;
       printf("commands are\n");
       while(ctx->cmds[i] != NULL)
       {
               printf("cmd #%d: [%s]\n", i, ctx->cmds[i]->cmd_with_args[0]);
               int j = 1;
               while(ctx->cmds[i]->cmd_with_args[j] != NULL)
               {
                       printf("\targ #%d: [%s]\n", j, ctx->cmds[i]->cmd_with_args[j]);
                      j++;
               }
               i++;
       }
    	printf("there are [%d] commands in line\n", ctx->cmd_cnt);  
}
*/

void print_ctx(t_context *ctx) {
	printf("\t=== print context ===\n");

	int i = 0;
	while (ctx->cmds[i] != NULL) {
		printf("cmd #%d: ", i);
		int j = 0;
		while (ctx->cmds[i]->cmd_with_args[j] != NULL) {
			printf(" [%s]", ctx->cmds[i]->cmd_with_args[j]);
			j++;
		}
		printf("\nred:\n");

		j = 0;
		while (ctx->cmds[i]->reds[j] != NULL) {
			printf("  [%s] of type [%d]\n",
				ctx->cmds[i]->reds[j]->fname_or_delim, 
				ctx->cmds[i]->reds[j]->type);
			j++;
		}
		printf("\n\n");
		i++;
	}
}

