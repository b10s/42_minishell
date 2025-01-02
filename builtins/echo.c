/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:47:33 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 01:31:40 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//ft_strncmp will be removed when libft is here
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		if (s1[i] == 0)
			break ;
		i++;
	}
	return (0);
}

void	echo(int fd, char **args)
{
	int	newline;
	int	i;
	int	j;

	newline = 1;
	if (ft_strncmp(args[0], "-n", 3) == 0)
	{
		newline = 0;
		args++;
	}
	i = 0;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			write(fd, &args[i][j], 1);
			j++;
		}
		i++;
		if (args[i] != NULL)
			write (fd, " ", 1);
	}
	if (newline)
		write (fd, "\n", 1);
}

