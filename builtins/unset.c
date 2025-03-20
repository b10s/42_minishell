/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:46:18 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/20 16:40:54 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	remove_var(char	*var, t_envs *envs)
{
	char	*name;

	name = get_name(var);
	if (name == NULL)
		return (EXIT_FAILURE);
	ft_unsetenv(name, envs);
	free(name);
	return (EXIT_SUCCESS);
}

//removes the variables by name
//args holds the strings of names
//it is null terminated
int	cmd_unset(char **args, t_envs *envs)
{
	int	i;

	if (args[0] == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (args[i] != NULL)
	{
		if (valid_var_check(args[i], CMD_UNSET) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		printf("got past var check!\n");
		if (remove_var(args[i], envs) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
