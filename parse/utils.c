/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/04/06 12:38:11 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

size_t	count_spaces_to_rm_near_redir(char *str)
{
	size_t	cnt;
	short	qq;
	short	qw;
	char	pre;

	pre = '\0';
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

int	cmd_size_till_pipe(char *cmd)
{
	short	qq;
	short	qw;
	int		len;

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
			break ;
		len++;
		cmd++;
	}
	return (len);
}

int	count_pipes(char *str)
{
	short	qq;
	short	qw;
	int		cnt;

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

int	count_commands(char **cmds)
{
	int	cnt;

	cnt = 0;
	while (cmds[cnt] != NULL)
		cnt++;
	return (cnt);
}

//TODO: create struct/type to hold qq, qw, sp/cnt to pass norm
// might be usefull for other funcs which have 25+ lines or 5+ vars
size_t	count_spaces_to_rm(char *str)
{
	size_t	cnt;
	short	flags[3];

	ft_bzero(flags, sizeof(flags));
	cnt = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && flags[QQ] == 0)
			flags[QW] = flags[QW] ^ 1;
		if (*str == '\"' && flags[QW] == 0)
			flags[QQ] = flags[QQ] ^ 1;
		if (*str == ' ' && flags[QQ] == 0 && flags[QW] == 0)
		{
			if (flags[SP] == 1)
				cnt++;
			flags[SP] = 1;
		}
		else
			flags[SP] = 0;
		str++;
	}
	return (cnt);
}
