/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/03/22 23:58:13 by aenshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

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

t_token	*get_next_token(char *str)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (tok == NULL)
		return (NULL);
	tok->beg = str;
	tok->len = get_token_len(str);
	tok->tok = NULL;
	if (tok->len == 0)
		return (tok);
	tok->tok = malloc(sizeof(char) * (tok->len + 1));
	if (tok->tok == NULL)
		return (NULL);
	tok->tok = ft_memcpy(tok->tok, str, tok->len);
	tok->tok[tok->len] = '\0';
	return (tok);
}
