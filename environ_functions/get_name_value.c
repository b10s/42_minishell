/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:56:03 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/20 17:24:25 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

char	*get_name(char *namevalue)
{
	int		namelen;
	char	*name;

	namelen = 0;
	while (namevalue[namelen] != '=' && namevalue[namelen] != '\0')
		namelen++;
	name = ft_substr(namevalue, 0, namelen);
	return (name);
}

char	*get_value(char *namevalue)
{
	int		valuelen;
	char	*value;

	valuelen = 0;
	while (*namevalue != '=')
	{
		if (*namevalue == '\0')
			return (ft_strdup(""));
		namevalue++;
	}
	namevalue++;
	while (namevalue[valuelen] != '\0')
		valuelen++;
	value = ft_substr(namevalue, 0, valuelen);
	return (value);
}

int	get_variable_pos(const char *name, t_envs *envs)
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
				return (i);
		}
		i++;
	}
	return (-1);
}
