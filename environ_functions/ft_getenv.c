/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:10:24 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/13 21:19:06 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

char	*ft_getenv(const char *name, t_envs *envs)
{
	int	namelen;
	int	i;

	namelen = ft_strlen(name);
	i = 0;
	while (envs->env_cpy[i] != NULL)
	{
		if (ft_strncmp(name, envs->env_cpy[i], namelen) == 0)
		{
			if (envs->env_cpy[i][namelen] == '=')
				return (envs->env_cpy[i] + namelen + 1);
		}
		i++;
	}
	return (NULL);
}
