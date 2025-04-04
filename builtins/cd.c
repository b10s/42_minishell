/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:23:38 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/02 21:49:20 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//changes working directory to path
//path here is the first 
int	cmd_cd(char **args, t_envs *envs)
{
	char	*path;

	if (args[0] == NULL)
	{
		path = ft_getenv("HOME", envs);
		if (path == NULL)
			return (ft_putstr_fd("cd: HOME not set\n", 2), EXIT_FAILURE);
	}
	else
		path = args[0];
	if (args[1] != NULL)
		return (ft_putstr_fd("cd: too many arguments\n", 2), EXIT_FAILURE);
	if (chdir(path) == -1)
	{
		if (errno == ENOMEM)
			exit(1);
		ft_putstr_fd("ch: ", STDERR_FILENO);
		perror(path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
