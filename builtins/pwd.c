/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:23:27 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/19 19:11:42 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//prints current working directory
int	cmd_pwd(void)
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
