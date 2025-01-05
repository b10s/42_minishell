/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:23:27 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/05 23:21:57 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(int fd)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (buff != NULL)
	{
		ft_putstr_fd(buff, fd);
		free(buff);
	}
	else
		perror("pwd: ");
}
