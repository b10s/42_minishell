/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:47:33 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/05 23:21:55 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo(int fd, char **args)
{
	int	newline;
	int	i;

	if (args[0] == NULL)
	{
		write(fd, "\n", 1);
		return ;
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
		ft_putstr_fd(args[i], fd);
		i++;
		if (args[i] != NULL)
			write (fd, " ", 1);
	}
	if (newline)
		write (fd, "\n", 1);
}
