/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:29:06 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/11 22:41:14 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	put_var(char *var)
{
	char	*name;
	char	*value;

	name = get_name(var);
	value = get_value(var);
	if (name == NULL || value == NULL)
		return (free(name), free(value), EXIT_FAILURE);
	ft_printf("declare -x ");
	ft_printf("%s=\"%s\"\n", name, value);
	free(name);
	free(value);
	return (EXIT_SUCCESS);
}

int	print_exported(t_envs *envs)
{
	int	i;

	i = 0;
	while (envs->env_cpy[i] != NULL)
	{
		put_var(envs->env_cpy[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	add_var(char *arg, t_envs *envs)
{
	char	*name;
	char	*value;

	name = get_name(arg);
	value = get_value(arg);
	if (ft_setenv(name, value, 1, envs) == EXIT_FAILURE)
		exit(1);
	return (EXIT_SUCCESS);
}

//if there are not arguments, export prints the list of exported variables
//otherwise it will update the variable and export status of the names given,
//if the name does not exist, the name is added to the vars linked list
//char **args looks like this {"NAME=var", "NAME2=var2", NULL}
int	cmd_export(char **args, t_envs *envs)
{
	int		i;

	if (args[0] == NULL)
		return (print_exported(envs));
	i = 0;
	while (args[i] != NULL)
	{
		if (valid_var_check(args[i], CMD_EXPORT) == EXIT_FAILURE)
		{
			i++;
			continue ;
		}
		if (add_var(args[i], envs) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
