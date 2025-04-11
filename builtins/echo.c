/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:47:33 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/11 22:35:03 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_newline(char **args, int *newline)
{
	int	i;
	int	j;

	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '-')
		{
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
				*newline = 0;
			else
				break ;
		}
		i++;
	}
	return (i);
}

//prints args to STDOUT with a space inbetween them, then adds a newline
//if there are no args it just adds a newline
//with "-n" string as first argument, no newline is added at the end
int	cmd_echo(char **args)
{
	int	newline;
	int	i;

	if (args[0] == NULL)
		return (printf("\n"), 0);
	newline = 1;
	args += is_newline(args, &newline);
	i = 0;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		i++;
		if (args[i] != NULL)
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
