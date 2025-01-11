/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:23:27 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/10 22:27:50 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (buff != NULL)
	{
		ft_putstr_fd(buff, STDOUT_FILENO);
		free(buff);
		return (0);
	}
	else
		return (perror("pwd: "), -1);
}
