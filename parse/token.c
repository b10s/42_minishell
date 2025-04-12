/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/04/12 17:07:08 by aenshin          ###   ########.fr       */
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
	int	flags[3];

	flags[QQ] = 0;
	flags[QW] = 0;
	flags[LEN] = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && flags[QQ] == 0)
			flags[QW] = flags[QW] ^ 1;
		else if (*str == '\"' && flags[QW] == 0)
			flags[QQ] = flags[QQ] ^ 1;
		if (flags[QW] == 1 || flags[QQ] == 1)
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
		flags[LEN]++;
	}
	return (flags[LEN]);
}

t_token	*get_next_token(char *str)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (tok == NULL)
		exit (1);
	tok->len = get_token_len(str);
	tok->tok = NULL;
	if (tok->len == 0)
		return (tok);
	tok->tok = ft_calloc((tok->len + 1), sizeof(char));
	if (tok->tok == NULL)
		exit (1);
	tok->tok = ft_memcpy(tok->tok, str, tok->len);
	tok->tok[tok->len] = '\0';
	return (tok);
}
