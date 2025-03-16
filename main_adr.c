/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/16 17:52:39 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/minishell.h"
#include "libft/libft.h"
#include "readline/readline.h"
#include "environ_functions/environ_functions.h"
#include "builtins/builtins.h"
#include "parse/parse.h"

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

int	main(void)
{
	char	*bread;
	char	*ham;

	bread = ft_strdup("abc$NAME!abc");
	ham = ft_strdup("VALUE");
	bread = sandwich(bread, 3, 3 + 1 + 4, ham);
	ft_printf("%s\n", bread);
}
