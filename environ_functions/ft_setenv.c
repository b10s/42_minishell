/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:14:55 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/07 18:35:33 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

char	*joined_name_value(const char *name, const char *value)
{
	char	*name_equals;
	char	*final;

	name_equals = ft_strjoin(name, "=");
	if (name_equals == NULL)
		return (NULL);
	final = ft_strjoin(name_equals, value);
	return (free(name_equals), final);
}

int	add_back_env_cpy(const char *name, const char *value, t_envs *envs)
{
	int		env_cpy_len;
	char	**old_env_cpy;
	int		i;

	old_env_cpy = envs->env_cpy;
	env_cpy_len = 0;
	while (old_env_cpy[env_cpy_len] != NULL)
		env_cpy_len++;
	envs->env_cpy = (char **)ft_calloc(env_cpy_len + 2, sizeof(char *));
	if (envs->env_cpy == NULL)
		return (free_split(old_env_cpy), EXIT_FAILURE);
	i = 0;
	while (i < env_cpy_len)
	{
		envs->env_cpy[i] = ft_strdup(old_env_cpy[i]);
		if (envs->env_cpy[i] == NULL)
			return (free_split(old_env_cpy), EXIT_FAILURE);
		i++;
	}
	free(old_env_cpy);
	envs->env_cpy[i] = joined_name_value(name, value);
	if (envs->env_cpy[i] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	find_and_replace(const char *name, const char *value, \
					char *n_v, t_envs *envs)
{
	int	i;

	i = 0;
	while (envs->env_cpy[i] != n_v)
		i++;
	free(n_v);
	envs->env_cpy[i] = joined_name_value(name, value);
	if (envs->env_cpy[i] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_setenv(const char *name, const char *value, int overwrite, t_envs *envs)
{
	char	*n_v;

	n_v = ft_getenv(name, envs);
	if (n_v == NULL)
		return (add_back_env_cpy(name, value, envs));
	else if (overwrite == 0)
		return (EXIT_SUCCESS);
	else
		return (find_and_replace(name, value, n_v, envs));
}
