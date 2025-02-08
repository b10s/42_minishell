/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:19:52 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/08 18:42:44 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

void	free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_env_cpy(char **env_cpy)
{
	free_split(env_cpy);
}

void	free_envs(t_envs *envs)
{
	if (envs == NULL)
		return ;
	free_env_cpy(envs->env_cpy);
	free(envs);
}
