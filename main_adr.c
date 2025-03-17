/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/17 23:09:25 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/minishell.h"
#include "libft/libft.h"
#include "readline/readline.h"
#include "environ_functions/environ_functions.h"
#include "ms/minishell.h"
#include "builtins/builtins.h"
#include "parse/parse.h"

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
	return(str);
}

int	main(void)
{
	char		*line;

	line = ft_strdup("e\"\'cho\" \"hel\"\"lo_\"w\'\"orld\"\'");
	ft_printf("%s\n", line);
	line = remove_a_layer_of_quotes(line);
	ft_printf("%s\n", line);
	free(line);
}
