/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:29:06 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/19 19:18:13 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_with_var_quotes(char *args)
{
	int	i;

	i = 0;
	while (args[i] != '\0')
	{
		write(1, args + i, 1);
		if (args[i] == '=')
			write(1, "\"", 1);
		i++;
	}
	if (ft_strchr(args, '=') != NULL)
		write(1, "\"", 1);
}

//prints the exported names
//quotes are added to the variable after the equals sign
//if there is no equals sign no quotes are added
//VAR=var becomes VAR="var"
//VAR would be printed as is
int	printf_exported(t_variable *vars)
{
	while (vars != NULL)
	{
		if (vars->exported == 1)
		{
			printf("declare -");
			if (vars->integer == 1)
				printf("i");
			if (vars->read_only == 1)
				printf("r");
			printf("x ");
			print_with_var_quotes(vars->content);
			printf("\n");
		}
		vars = vars->next;
	}
	return (EXIT_SUCCESS);
}

//adds a node to the end of vars, vars_last is the last node
//the node is set as exported
int	add_exported(char *arg, t_variable *vars_last)
{
	t_variable	*new_var;

	new_var = (t_variable *)ft_calloc(1, sizeof(t_variable));
	if (new_var == NULL)
		return (EXIT_FAILURE);
	new_var->exported = 1;
	new_var->content = ft_strdup(arg);
	if (new_var->content == NULL)
		return (free(new_var), EXIT_FAILURE);
	vars_last->next = new_var;
	return (EXIT_SUCCESS);
}

//loops through vars, if the name exists in vars then necessary updates are made
//if name does not exist in vars, the name is added to the list
int	vars_check_loop(char **args, t_variable *vars, int end_or_eq, int i)
{
	while (vars != NULL)
	{
		if (ft_strncmp(args[i], vars->content, end_or_eq) == 0 \
		&& (args[i][end_or_eq] == '\0' || args[i][end_or_eq] == '=') \
		&& (vars->content[end_or_eq] == '\0' || \
			vars->content[end_or_eq] == '='))
		{
			vars->exported = 1;
			if (args[i][end_or_eq] == '=')
			{
				free(vars->content);
				vars->content = ft_strdup(args[i]);
			}
			if (vars->content == NULL)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		if (vars->next == NULL)
			return (add_exported(args[i], vars));
		vars = vars->next;
	}
	return (EXIT_FAILURE);
}

//if there are not arguments, export prints the list of exported variables
//otherwise it will update the variable and export status of the names given,
//if the name does not exist, the name is added to the vars linked list
//char **args looks like this {"NAME=var", "NAME2=var2", "NAME3"}
//as seen with NAME3 it is not necessary to give the name a value
int	cmd_export(char **args, t_variable *vars)
{
	int			end_or_eq;
	int			i;

	if (args[0] == NULL)
		return (printf_exported(vars));
	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL)
			end_or_eq = ft_strchr(args[i], '=') - args[i];
		else
			end_or_eq = ft_strlen(args[i]);
		if (vars_check_loop(args, vars, end_or_eq, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
