/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpolate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:11:18 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/16 20:10:04 by adrgutie         ###   ########.fr       */
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

int	name_check(char *name)
{
	int	i;

	i = 0;
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

char	*update_line(char *line, t_envs *envs, int *i, int single_quotes_flag)
{
	int		namelen;
	char	*name;
	char	*value;
	int		emptycheck;

	namelen = name_check(&(line[*i + 1]));
	if (namelen == -1)
		return (line);
	name = ft_substr(line, *i + 1, namelen);
	if (name == NULL)
		return (free(line), NULL);
	value = ft_getenv(name, envs);
	if (value == NULL)
		value = "";
	value = ft_strdup(value);
	if (value == NULL)
		return (NULL);
	emptycheck = 0;
	if (value[0] == '\0')
		emptycheck = 1;
	line = sandwich(line, *i, *i + 1 + namelen, value);
	if (emptycheck == 1)
		(*i)--;
	return (line);
}

char	*ft_interpolate(char *line, t_envs *envs, t_context *ctx)
{
	int		single_quotes_flag;
	int		i;
	int		namelen;

	single_quotes_flag = -1;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			single_quotes_flag *= -1;
		if (line[i] == '$' && single_quotes_flag == -1)
		{
			line = update_line(line, envs, &i, single_quotes_flag);
			if (line == NULL)
				return (ctx->is_fatal = 1, NULL);
		}
		i++;
	}
	return (line);
}
