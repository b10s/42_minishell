/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:42:52 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/12 23:45:54 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//printfs out all the environment variables in env
int	cmd_env(t_envs *envs)
{
	int	i;

	i = 0;
	while (envs->env_cpy[i] != NULL)
	{
		ft_printf("%s\n", envs->env_cpy[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
