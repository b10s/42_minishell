/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:15:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/08 19:29:21 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

int	ft_unsetenv(const char *name, t_envs *envs)
{
	char	*n_v;
	int		i;

	n_v = ft_getenv(name, envs);
	if (n_v == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (envs->env_cpy[i] != n_v)
		i++;
	free(n_v);
	while (envs->env_cpy[i + 1] != NULL)
	{
		envs->env_cpy[i] = envs->env_cpy[i + 1];
		i++;
	}
	envs->env_cpy[i] = NULL;
	return (EXIT_SUCCESS);
}
