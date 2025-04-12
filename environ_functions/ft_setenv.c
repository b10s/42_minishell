/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:14:55 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/12 17:52:53 by adrgutie         ###   ########.fr       */
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
			exit(1);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	remake_env_cpy_bigger(t_envs *envs)
{
	int		oldlen;
	char	**newenv;

	oldlen = count_variables(envs);
	newenv = (char **)ft_calloc(oldlen + 2, sizeof(char *));
	if (newenv == NULL)
		exit(1);
	copy_env_cpy(newenv, envs);
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
		exit(1);
	name_eq_value = ft_strjoin(name_eq, value);
	if (name_eq_value == NULL)
		exit(1);
	free(name_eq);
	i = 0;
	while (envs->env_cpy[i] != NULL)
		i++;
	envs->env_cpy[i] = name_eq_value;
	return (EXIT_SUCCESS);
}

int	ft_setenv(const char *name, const char *value, int overwrite, t_envs *envs)
{
	int	var_pos;

	var_pos = get_variable_pos(name, envs);
	if (var_pos == -1)
		remake_env_cpy_bigger(envs);
	else if (overwrite == 0)
		return (EXIT_SUCCESS);
	else
	{
		free(envs->env_cpy[var_pos]);
		envs->env_cpy[var_pos] = NULL;
	}
	return (add_var(name, value, envs));
}
