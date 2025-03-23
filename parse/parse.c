/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/03/23 23:39:00 by aenshin          ###   ########.fr       */
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

	// no need cmds, commands?
	t_cmd		**cmds;
	char		**commands;

	t_red		**reds;
	t_red		*red;
	char		*pos_in_cmd;
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
	if (validate_quotes(line) != 0)
	{
		ctx->err = (char *)&QUOTES_ERR;
		return (ctx);
	}

	//TODO move line grooming in separate func

	//TODO exit if malloc err, free inside
	tmp = rm_multi_spaces(line);
	free(line);
	line = tmp;

	//TODO exit if malloc err, free inside
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
	// line grooming till here

	commands = split_pipes(line);
	if (commands == NULL)
	{
		return (NULL);
	}
	ctx->cmd_cnt = count_commands(commands);
	free(ctx->cmds);
	ctx->cmds = ft_calloc(ctx->cmd_cnt, sizeof(t_cmd *));

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
