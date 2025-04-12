/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/04/12 21:08:17 by aenshin          ###   ########.fr       */
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
	commands = split_pipes(line);
	free(line);
	if (commands == NULL)
		return (NULL);
	ctx->cmd_cnt = count_commands(commands);
	ctx->cmds = ft_calloc((ctx->cmd_cnt + 1), sizeof(t_cmd *));
	if (ctx->cmds == NULL)
		exit(1);
	parse_commands(ctx, commands);
	interp_remquotelayer(ctx, ms);
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
		ctx->cmds[i] = ft_calloc(1, sizeof(t_cmd));
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

//NOTE: since there is syntax check before parse,
// no need to return err in ctx
//  $ >
//TODO: set ctx with err msg: unknown char beginning of token
// after call of parse_words()
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
		if (parse_words(&wrds, &pos, &a[WRD_CNT], &a[WRD_MAX]) == 1)
			return (1);
	}
	ctx->cmds[cmd_idx]->reds = reds;
	ctx->cmds[cmd_idx]->cmd_with_args = wrds;
	return (0);
}

// TODO: verify where fatal err, err, ok
// TODO: set ctx err - when tok-<len is 0
// can't parse token but not end of line
// TODO: check result of add_word
int	parse_words(char ***wrds, char **pos, int *wrd_cnt, int *wrd_max)
{
	t_token		*tok;

	tok = get_next_token(*pos);
	if (tok->len == 0)
	{
		return (1);
	}
	add_word(wrds, tok->tok, wrd_cnt, wrd_max);
	*pos = *pos + tok->len;
	free(tok->tok);
	free(tok);
	return (0);
}

// TODO: test what substr returns in case 0, 0
//		empty string or NULL? e.g. `a|b|` 
//TODO check what count_pipes may return
//TODO check what substr, strtrim may return
//TODO what to return if str == NULL
//NOTE pipes + 2 in case of 0 pipes will eat extra 8 bytes but it is okay
char	**split_pipes(char *str)
{
	char	**cmds;
	char	**ptr;
	char	*tmp;

	cmds = ft_calloc((count_pipes(str) + 2), sizeof(char *));
	if (cmds == NULL)
		exit (1);
	ptr = cmds;
	while (cmd_size_till_pipe(str) != 0)
	{
		*cmds = ft_substr(str, 0, cmd_size_till_pipe(str));
		tmp = ft_strtrim(*cmds, " ");
		free(*cmds);
		*cmds = tmp;
		if (tmp == NULL)
			return (NULL);
		cmds++;
		str = str + cmd_size_till_pipe(str);
		if (*str == '|')
			str++;
	}
	return (ptr);
}
