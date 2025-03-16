/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpolate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:11:18 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/16 16:55:13 by adrgutie         ###   ########.fr       */
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
	if (ft_isalpha(name[i]) != 1 && name[i] != '_')
		return (EXIT_FAILURE);
	while (name[i] != '\0' && )
	{
		if (ft_isalnum(name[i]) != 1 && name[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
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

char	*ft_interpolate(char *line, t_minishell *ms)
{
	int	single_quotes_flag;
	int	i;

	single_quotes_flag = -1;
	i = 0;
	while(line[i] != NULL)
	{
		if (line[i] == '\'')
			single_quotes_flag *= -1;
		
	}
}