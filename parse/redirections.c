/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/04/13 18:43:50 by aenshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

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
	red = ft_calloc(1, sizeof(t_red));
	if (red == NULL)
		exit (1);
	red->type = type;
	red->fname_or_delim = tok->tok;
	free(tok);
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
