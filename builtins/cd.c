/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:23:38 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/19 19:18:20 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//changes working directory to path
int	cmd_cd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("ch: ", STDERR_FILENO);
		perror(path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
