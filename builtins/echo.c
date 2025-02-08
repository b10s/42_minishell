/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:47:33 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/08 19:41:09 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
	if (ft_strncmp(args[0], "-n", 3) == 0)
	{
		if (args[1] == NULL)
			return (EXIT_SUCCESS);
		newline = 0;
		args++;
	}
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
