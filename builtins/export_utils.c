/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:16:00 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/01 14:08:36 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	printnotvalid(char *v_n, int which_cmd)
{
	if (which_cmd == CMD_EXPORT)
		ft_putstr_fd("export: ", 2);
	else if (which_cmd == CMD_UNSET)
		ft_putstr_fd("unset: ", 2);
	ft_putstr_fd(v_n, 2);
	ft_putendl_fd(": not a valid identifier", 2);
}

int	name_check(char *name)
{
	int	i;

	i = 0;
	if (ft_isalpha(name[i]) != 1 && name[i] != '_')
		return (EXIT_FAILURE);
	while (name[i] != '\0')
	{
		if (ft_isalnum(name[i]) != 1 && name[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	value_check(char *value)
{
	int	i;

	if (value[0] == '\0')
		return (EXIT_SUCCESS);
	i = 0;
	while (value[i] != '\0')
	{
		if (ft_isprint(value[i]) != 1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

//checks if the name and value is valid
//the name can only start with a letter or an '_'
//it can be followed by letter '_' or number
//the value is more flexible, it allows printable characters or
//an empty string
int	valid_var_check(char *v_n, int which_cmd)
{
	char	*name;
	char	*value;
	int		fail;

	fail = 0;
	if (ft_strchr(v_n, '=') == NULL && which_cmd == CMD_EXPORT)
		return (printnotvalid(v_n, which_cmd), EXIT_FAILURE);
	name = get_name(v_n);
	value = get_value(v_n);
	if (name == NULL || value == NULL)
		exit(1);
	if (name_check(name) == EXIT_FAILURE)
		fail = 1;
	else if (value_check(value) == EXIT_FAILURE)
		fail = 1;
	free(name);
	free(value);
	if (fail == 1)
		return (printnotvalid(v_n, which_cmd), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
