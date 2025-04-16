/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/03/23 23:41:59 by aenshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

// TODO free if NULL
t_context	*init_ctx(void)
{
	t_context	*ctx;

	ctx = ft_calloc(1, sizeof(t_context));
	if (ctx == NULL)
		exit (1);
	ctx->cmds = NULL;
	ctx->err = NULL;
	ctx->cmd_cnt = 0;
	ctx->pipe_read = -1;
	ctx->pipe_read_index = -1;
	return (ctx);
}

int	count_single_quotes(char *str)
{
	short	qw;
	short	qq;
	int		res;

	res = 0;
	qw = 0;
	qq = 0;
	while (*str != '\0')
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

int	count_double_quotes(char *str)
{
	short	qw;
	short	qq;
	int		res;

	res = 0;
	qw = 0;
	qq = 0;
	while (*str != '\0')
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

int	validate_quotes(char *str)
{
	if (count_single_quotes(str) % 2 != 0)
		return (1);
	if (count_double_quotes(str) % 2 != 0)
		return (1);
	return (0);
}
