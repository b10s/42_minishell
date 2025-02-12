/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/12 23:47:40 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include "../libft/libft.h"

extern char				**environ;

typedef struct s_envs
{
	char		**env_cpy;
}	t_envs;

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

int	cpy_env(t_envs *envs)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	envs->env_cpy = (char **)ft_calloc(i + 1, sizeof(char *));
	if (envs->env_cpy == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (environ[i] != NULL)
	{
		envs->env_cpy[i] = ft_strdup(environ[i]);
		if (envs->env_cpy[i] == NULL)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

t_envs	*init_envs(void)
{
	t_envs	*envs;

	envs = (t_envs *)ft_calloc(1, sizeof(t_envs));
	if (envs == NULL)
		return (NULL);
	if (cpy_env(envs) == EXIT_FAILURE)
		return (free_envs(envs), NULL);
	return (envs);
}


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
			if (envs->env_cpy[i][namelen] == '=' || \
				envs->env_cpy[i][namelen] == '\0')
			{
				return (envs->env_cpy[i]);
			}
		}
		i++;
	}
	return (NULL);
}


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

int	cmd_env(t_envs *envs)
{
	int	i;

	i = 0;
	while (envs->env_cpy[i] != NULL)
	{
		ft_printf("%s\n", envs->env_cpy[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(void)
{
	t_envs	*envs;

	envs = init_envs();
	if (envs == NULL)
		return (EXIT_FAILURE);
	ft_setenv("POOP", "", 1, envs);
	cmd_env(envs);
	free_envs(envs);
	return (EXIT_SUCCESS);
}
