/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 04:06:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/06 11:52:30 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_not_special(char *line)
{
	int	i;
	char *special;

	special = "|<>";
	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strchr(special, line[i]) == NULL && line[i] != '\0')
		return (1);
	return (0);
}

int	is_here_doc(char *line)
{
	int	i;
	int	dq;
	int	sq;

	dq = 0;
	sq = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			sq = sq ^ 1;
		if (line[i] == '\"')
			dq = dq ^ 1;
		if (line[i] == '<' && dq == 0 && sq == 0)
		{
			if (line[i + 1] == '<')
				return (next_not_special(line + i + 2));
		}
		i++;
	}
	return (0);
}
