/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/04/12 20:48:27 by aenshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

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
		exit(1);
	tmp = ft_strtrim(line, " ");
	free(line);
	line = tmp;
	if (line == NULL)
		exit(1);
	return (line);
}

// do not remove spaces in ' hey ' and in " hi "
char	*rm_multi_spaces(char *str)
{
	size_t	spaces_to_rm;
	size_t	str_len;
	char	*new_str;
	short	flags[3];

	flags[QQ] = 0;
	flags[QW] = 0;
	flags[SP] = 0;
	spaces_to_rm = count_spaces_to_rm(str);
	str_len = ft_strlen(str);
	new_str = ft_calloc(str_len - spaces_to_rm + 1, sizeof(char));
	if (new_str == NULL)
		exit (1);
	rm_ml_sp(new_str, str, flags);
	return (new_str);
}

void	rm_ml_sp(char *new_str, char *str, short flags[3])
{
	while (*str != '\0')
	{
		if (*str == '\'' && flags[QQ] == 0)
			flags[QW] = flags[QW] ^ 1;
		if (*str == '\"' && flags[QW] == 0)
			flags[QQ] = flags[QQ] ^ 1;
		if (is_space(*str) == 1 && flags[QQ] == 0 && flags[QW] == 0)
		{
			if (flags[SP] != 1)
			{
				*new_str = *str;
				new_str++;
			}
			flags[SP] = 1;
		}
		else
		{
			flags[SP] = 0;
			*new_str = *str;
			new_str++;
		}
		str++;
	}
	*new_str = '\0';
}

//TODO: free if there is mem leak: str, new_str - check caller
char	*rm_spaces_near_redir(char *str)
{
	size_t	new_len;
	short	a[2];
	char	*new_str;
	char	pre;

	pre = '\0';
	new_len = ft_strlen(str) - count_spaces_to_rm_near_redir(str) + 1;
	new_str = ft_calloc(new_len, sizeof(char));
	if (new_str == NULL)
		exit (1);
	a[QQ] = 0;
	a[QW] = 0;
	rm_sp_near_red(new_str, str, pre, a);
	return (new_str);
}

void	rm_sp_near_red(char *new_str, char *str, char pre, short a[2])
{
	while (*str != '\0')
	{
		if (*str == '\'' && a[QQ] == 0)
			a[QW] = a[QW] ^ 1;
		if (*str == '\"' && a[QW] == 0)
			a[QQ] = a[QQ] ^ 1;
		*new_str = *str;
		if ((*str == '<' || *str == '>') && a[QQ] == 0 && a[QW] == 0)
		{
			if (is_space(pre) == 1)
			{
				new_str--;
				*new_str = *str;
			}
		}
		if (is_space(*str) == 1 && a[QQ] == 0 && a[QW] == 0)
			if (pre == '<' || pre == '>')
				new_str--;
		pre = *str;
		str++;
		new_str++;
	}
	*new_str = '\0';
}
