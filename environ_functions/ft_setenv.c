/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:14:55 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/13 21:28:09 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

int	count_variables(t_envs *envs)
{
	int	len;

	len = 0;
	while (envs->env_cpy[len] != NULL)
		len++;
	return (len);
}

int	copy_env_cpy(char **newenv, t_envs *envs)
{
	int	i;

	i = 0;
	while (envs->env_cpy[i] != NULL)
	{
		newenv[i] = ft_strdup(envs->env_cpy[i]);
		if (newenv[i] == NULL)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	remake_env_cpy_bigger(t_envs *envs)
{
	int		oldlen;
	char	**newenv;

	oldlen = count_variables(envs);
	newenv = (char **)ft_calloc(oldlen, sizeof(char *));
	if (newenv == NULL)
		return (EXIT_FAILURE);
	if (copy_env_cpy(newenv, envs) == EXIT_FAILURE)
		return (free_split(newenv), EXIT_FAILURE);
	free_split(envs->env_cpy);
	envs->env_cpy = newenv;
	return (EXIT_SUCCESS);
}

int	add_var(const char *name, const char *value, t_envs *envs)
{
	char	*name_eq;
	char	*name_eq_value;
	int		i;

	name_eq = ft_strjoin(name, "=");
	if (name_eq == NULL)
		return (EXIT_FAILURE);
	name_eq_value = ft_strjoin(name_eq, value);
	if (name_eq_value == NULL)
		return (free(name_eq), EXIT_FAILURE);
	i = 0;
	while (envs->env_cpy[i] != NULL)
		i++;
	envs->env_cpy[i] = name_eq_value;
	free(name_eq);
	return (EXIT_SUCCESS);
}

int	ft_setenv(const char *name, const char *value, int overwrite, t_envs *envs)
{
	int	var_pos;

	var_pos = get_variable_pos(name, envs);
	if (var_pos == -1)
	{
		if (remake_env_cpy_bigger(envs) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (overwrite == 0)
		return (EXIT_SUCCESS);
	else
	{
		free(envs->env_cpy[var_pos]);
		envs->env_cpy[var_pos] == NULL;
	}
	return (add_var(name, value, envs));
}
