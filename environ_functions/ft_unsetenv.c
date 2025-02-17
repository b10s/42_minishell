/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:15:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/15 13:26:20 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

//removes the variable with name
//does not reallocate the array since it is not necessary to do so
int	ft_unsetenv(const char *name, t_envs *envs)
{
	int	v_pos;	

	v_pos = get_variable_pos(name, envs);
	if (v_pos == -1)
		return (EXIT_SUCCESS);
	while (envs->env_cpy[v_pos + 1] != NULL)
	{
		envs->env_cpy[v_pos] = envs->env_cpy[v_pos + 1];
		v_pos++;
	}
	free(envs->env_cpy[v_pos]);
	envs->env_cpy[v_pos] = NULL;
	return (EXIT_SUCCESS);
}
