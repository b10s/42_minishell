/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_a_layer_of_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:00:09 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/17 23:03:13 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*remove_a_layer_of_quotes(char *str)
{
	int		i;
	int		j;
	char	current_quote_type;

	current_quote_type = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\"' || str[i] == '\'') && current_quote_type == 0)
			current_quote_type = str[i];
		else if (current_quote_type == str[i])
			current_quote_type = 0;
		else
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}
