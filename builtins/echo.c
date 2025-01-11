/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:47:33 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/10 22:27:48 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo(char **args)
{
	int	newline;
	int	i;

	if (args[0] == NULL)
	{
		printf("\n");
		return (0);
	}
	newline = 1;
	if (ft_strncmp(args[0], "-n", 3) == 0)
	{
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
	return (0);
}
