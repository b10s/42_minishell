/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:23:38 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/11 23:38:45 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//changes working directory to path
int	cd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("ch: ", STDERR_FILENO);
		perror(path);
		return (-1);
	}
	return (0);
}
