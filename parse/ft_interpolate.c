/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpolate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:11:18 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/28 18:42:25 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	*join_line_newline(char *lines, char *to_join)
{
	char	*newline;

	if (lines == NULL || to_join == NULL)
		return (free(lines), free(to_join), NULL);
	newline = ft_strjoin(lines, to_join);
	free(lines);
	free(to_join);
	return (newline);
}

static int	name_check(char *name)
{
	int	i;

	i = 0;
	if (name[i] == '?')
		return (1);
	if (ft_isalpha(name[i]) != 1 && name[i] != '_')
		return (-1);
	while (1)
	{
		if (ft_isalnum(name[i]) != 1 && name[i] != '_')
			break ;
		i++;
	}
	return (i);
}

char	*sandwich(char *bread, int start, int end, char *ham)
{
	int		len_bread;
	char	*temp;
	char	*bread_ham;

	len_bread = ft_strlen(bread) - (end - start);
	temp = ft_substr(bread, 0, start);
	bread_ham = join_line_newline(temp, ham);
	temp = ft_substr(bread, end, len_bread);
	free(bread);
	return (join_line_newline(bread_ham, temp));
}

char	*update_line(char *line, t_minishell *ms, \
				int *i)
{
	int		namelen;
	char	*name;
	char	*value;
	int		value_len;

	namelen = name_check(&(line[*i + 1]));
	if (namelen == -1)
		return (line);
	name = ft_substr(line, *i + 1, namelen);
	if (name == NULL)
		return (free(line), NULL);
	value = ft_getenv(name, ms->envs);
	if (value == NULL)
		value = "";
	if (name[0] == '?')
		value = ft_itoa(ms->exit_status);
	else
		value = ft_strdup(value);
	if (value == NULL)
		return (NULL);
	value_len = ft_strlen(value);
	line = sandwich(line, *i, *i + 1 + namelen, value);
	(*i) += (value_len - 1);
	return (line);
}

char	*ft_interpolate(char *line, t_minishell *ms, int quote_check)
{
	int		single_quotes_flag;
	int		i;

	single_quotes_flag = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			single_quotes_flag = single_quotes_flag ^ 1;
		if (line[i] == '$' && ((single_quotes_flag && quote_check) == 0))
		{
			line = update_line(line, ms, &i);
			if (line == NULL)
				exit(1);
		}
		i++;
	}
	return (line);
}
