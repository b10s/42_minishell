/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:19:52 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/06 15:17:18 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

static void	free_split(char **split)
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

void	free_vars(t_variable **vars)
{
	t_variable	*prev;

	while (*vars != NULL)
	{
		prev = *vars;
		free(prev->name);
		free(prev->value);
		(*vars) = (*vars)->next;
		free(prev);
	}
}

void	free_envs(t_envs *envs)
{
	if (envs == NULL)
		return ;
	free_env_cpy(envs->env_cpy);
	free_vars(&(envs->vars));
	free(envs);
}
