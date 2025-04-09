/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/03/23 23:48:58 by aenshin          ###   ########.fr       */
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
	char		**commands;

	ctx = init_ctx();
	if (validate_quotes(line) != 0)
	{
		ctx->err = (char *)&QUOTES_ERR;
		return (ctx);
	}
	line = remove_spaces(line);
	if (line == NULL)
		return (NULL);
	commands = split_pipes(line);
	if (commands == NULL)
		return (NULL);
	ctx->cmd_cnt = count_commands(commands);
	ctx->cmds = ft_calloc((ctx->cmd_cnt + 1), sizeof(t_cmd *));
	if (ctx->cmds == NULL)
		exit (1);
	parse_commands(ctx, commands);
	if (interp_remquotelayer(ctx, ms) == EXIT_FAILURE)
		return (free_ctx(ctx, ms), NULL);
	return (ctx);
}

//TODO: all previosly retrun NULL replace with set err,
// free uneeded and make sure ctx with err is returned
void	parse_commands(t_context *ctx, char **commands)
{
	int			i;
	int			a[4];

	a[RED_CNT] = 0;
	a[RED_MAX] = 5;
	a[WRD_CNT] = 0;
	a[WRD_MAX] = 5;

	i = 0;
	while (i < ctx->cmd_cnt)
	{
		ctx->cmds[i] = malloc(sizeof(t_cmd));
		if (ctx->cmds[i] == NULL)
			exit (1);
		ctx->cmds[i]->out_fd = -1;
		ctx->cmds[i]->in_fd = -1;
		ctx->cmds[i]->here_doc_filename = NULL;
		ctx->cmds[i]->cmd_with_args = NULL;
		ctx->cmds[i]->reds = NULL;
		if (parse_single_cmd(commands[i], i, a, ctx) != 0)
			break ;
		i++;
	}
}

//TODO: free token?
//TODO: set err and return ctx
// $ >
// bash: syntax error near unexpected token `newline'
t_red	*get_redirection(char **pos_in_cmd, int skip, int type)
{
	t_red		*red;
	t_token		*tok;

	*pos_in_cmd = *pos_in_cmd + skip;
	tok = get_next_token(*pos_in_cmd);
	if (tok->len == 0)
		return (NULL);
	*pos_in_cmd = *pos_in_cmd + tok->len;
	red = malloc(sizeof(t_red *));
	if (red == NULL)
		exit (1);
	red->type = type;
	red->fname_or_delim = tok->tok;
	return (red);
}

void	free_red(t_red *red)
{
	if (red != NULL)
	{
		free(red->fname_or_delim);
		free(red);
	}
}

//NOTE: since there is syntax check before parse,
// no need to return err in ctx
//  $ >
int	parse_single_cmd(char *pos, int cmd_idx, int a[4], t_context *ctx)
{
	t_red		**reds;
	char		**wrds;

	wrds = ft_calloc((a[WRD_MAX] + 1), sizeof(char *));
	reds = ft_calloc((a[RED_MAX] + 1), sizeof(t_red *));
	if (wrds == NULL || reds == NULL)
		exit (1);
	while (*pos != '\0')
	{
		if (*pos == ' ')
		{
			pos++;
			continue ;
		}
		if (parse_reds(&reds, &pos, &a[RED_CNT], &a[RED_MAX]) == 1)
			continue ;
		//TODO: set ctx with err msg: unknown char beginning of token
		if (parse_words(&wrds, &pos, &a[WRD_CNT], &a[WRD_MAX]) == 1)
			return (1);
	}
	ctx->cmds[cmd_idx]->reds = reds;
	ctx->cmds[cmd_idx]->cmd_with_args = wrds;
	return (0);
}

int	parse_words(char ***wrds, char **pos, int *wrd_cnt, int *wrd_max)
{
	t_token		*tok;
	// parse word
	tok = get_next_token(*pos);
	// TODO: fatal err, err, ok
	if (tok->len == 0)
	{
		// can't parse token but not end of line
		// TODO: set ctx err
		return (1);
	}
	// TODO: check result
	add_word(wrds, tok->tok, wrd_cnt, wrd_max);
	*pos = *pos + tok->len;
	return (0);
}

t_red	*get_red(char **pos)
{
	t_red	*red;
	char	*pos_in_cmd;

	pos_in_cmd = *pos;
	red = NULL;
	if (*pos_in_cmd == '>')
	{
		if (pos_in_cmd[1] == '>')
			red = get_redirection(&pos_in_cmd, 2, OUT_APPEND);
		else
			red = get_redirection(&pos_in_cmd, 1, OUT);
	}
	else if (*pos_in_cmd == '<')
	{
		if (pos_in_cmd[1] == '<')
			red = get_redirection(&pos_in_cmd, 2, HERE_DOC);
		else
			red = get_redirection(&pos_in_cmd, 1, IN);
	}
	*pos = pos_in_cmd;
	return (red);
}

// TODO: check result or add_redirection
// returns 1 if parsed, 0 if nothing found
int	parse_reds(t_red ***reds, char **pos, int *red_cnt, int *red_max)
{
	char	*pos_in_cmd;
	t_red	*red;

	pos_in_cmd = *pos;
	red = NULL;

	red = get_red(&pos_in_cmd);
	if (red != NULL)
	{
		add_reds(reds, red, red_cnt, red_max);
		*pos = pos_in_cmd;
		free_red(red);
		return (1);
	}
	return (0);
}

//TODO exit if malloc err, free inside
char	*remove_spaces(char *line)
{
	char		*tmp;

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
	return (line);
}

char	*rm_spaces_near_redir(char *str)
{
	size_t	new_len;
	short	qq;
	short	qw;
	char	*new_str;
	char	pre;
	char	*tmp;

	pre = '\0';
	new_len = ft_strlen(str) - count_spaces_to_rm_near_redir(str) + 1;
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
		{
			if (pre == ' ')
			{
				new_str--;
				*new_str = *str;
			}
		}
		if (*str == ' ' && qq == 0 && qw == 0)
			if (pre == '<' || pre == '>')
				new_str--;
		pre = *str;
		str++;
		new_str++;
	}
	*new_str = '\0';
	return (tmp);
}

// TODO: test what substr returns in case 0, 0
		//		empty string or NULL? e.g. `a|b|` 
char	**split_pipes(char *str)
{
	char	**cmds;
	char	**ptr;
	char	*tmp;
	int		cmd_len;
	int		cmd_cnt;

	cmds = NULL;
	if (str == NULL)
		return (NULL);
	cmd_cnt = count_pipes(str);
	cmds = malloc(sizeof(char *) * (cmd_cnt + 1));
	if (cmds == NULL)
		return (NULL);
	ptr = cmds;
	cmd_len = cmd_size_till_pipe(str);
	while (cmd_len != 0)
	{
		*cmds = ft_substr(str, 0, cmd_len);
		tmp = ft_strtrim(*cmds, " ");
		free(*cmds);
		*cmds = tmp;
		if (tmp == NULL)
			return (NULL);
		if (*cmds == NULL)
			return (NULL);
		cmds++;
		str = str + cmd_len;
		if (*str == '|')
			str++;
		cmd_len = cmd_size_till_pipe(str);
	}
	*cmds = NULL;
	return (ptr);
}

// do not remove spaces in ' hey ' and in " hi "
char	*rm_multi_spaces(char *str)
{
	size_t	spaces_to_rm;
	size_t	str_len;
	char	*new_str;
	char	*tmp;
	short	qw;
	short	qq;
	short	sp;

	qq = 0;
	qw = 0;
	sp = 0;
	spaces_to_rm = count_spaces_to_rm(str);
	str_len = ft_strlen(str);
	new_str = malloc(str_len - spaces_to_rm + 1);
	if (new_str == NULL)
		exit (1);
	tmp = new_str;
	while (*str != '\0')
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
		}
		else
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
