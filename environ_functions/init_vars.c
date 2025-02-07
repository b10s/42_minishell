/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:48:57 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/06 16:21:00 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

char	*get_name(char *name_value)
{
	char	*name;
	int		namelen;

	namelen = 0;
	while (name_value[namelen] != '=' && name_value[namelen] != '\0')
		namelen++;
	name = ft_substr(name_value, 0, namelen);
	return (name);
}

char	*get_value(char *name_value)
{
	while (*name_value != '=' && *name_value != '\0')
		name_value++;
	if (*name_value == '\0')
		return (NULL);
	name_value++;
	if (*name_value == '\0')
		return ((char *)ft_calloc(1, sizeof(char)));
	else
		return (ft_strdup(name_value));
}

t_variable	*new_variable(char *name_value)
{
	t_variable	*new_var;
	char		*name;
	char		*value;

	new_var = (t_variable *)ft_calloc(1, sizeof(t_variable));
	name = get_name(name_value);
	value = get_value(name_value);
	if (name == NULL || value == NULL || new_var == NULL)
		return (free(name), free(value), free(new_var), NULL);
	new_var->name = name;
	new_var->value = value;
	new_var->next = NULL;
}

void	add_variable_back(t_variable **vars, t_variable *new_var)
{
	t_variable	*first;

	if (*vars == NULL)
	{
		*vars = new_var;
		return ;
	}
	first = (*vars);
	while ((*vars)->next != NULL)
		(*vars) = (*vars)->next;
	(*vars)->next = new_var;
	(*vars) = first;
}

int	init_vars(t_envs *envs)
{
	int			i;
	t_variable	*new_var;

	i = 0;
	while (envs->env_cpy[i] != NULL)
	{
		new_var = new_variable(envs->env_cpy[i]);
		if (new_var == NULL)
			return (EXIT_FAILURE);
		add_variable_back(&(envs->vars), new_var);
		i++;
	}
	return (EXIT_SUCCESS);
}
