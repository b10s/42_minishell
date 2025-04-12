/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:13:10 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/12 18:00:15 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

int	cpy_env(t_envs *envs)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	envs->env_cpy = (char **)ft_calloc(i + 1, sizeof(char *));
	if (envs->env_cpy == NULL)
		exit(1);
	i = 0;
	while (environ[i] != NULL)
	{
		envs->env_cpy[i] = ft_strdup(environ[i]);
		if (envs->env_cpy[i] == NULL)
			exit(1);
		i++;
	}
	return (EXIT_SUCCESS);
}

t_envs	*init_envs(void)
{
	t_envs	*envs;

	envs = (t_envs *)ft_calloc(1, sizeof(t_envs));
	if (envs == NULL)
		exit(1);
	cpy_env(envs);
	return (envs);
}
