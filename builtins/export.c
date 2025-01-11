/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:29:06 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/10 22:28:05 by adrgutie         ###   ########.fr       */
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

int	export(char **args, t_variable *vars)
{
	int			i;

	if (args[0] == NULL)
		return (printf_exported(vars));
	i = 0;
	while (args[0][i] != '\0' && args[0][i] != '=')
		i++;
	while (1)
	{
		if (ft_strncmp(args[0], vars->content, i) == 0 \
		&& ((args[0][i] == '\0' || args[0][i] == '=') \
		&& (vars->content[i] == '\0' || vars->content[i] == '=')))
		{
			vars->exported = 1;
			if (args[0][i] == '=')
				vars->content = ft_strdup(args[0]);
			if (vars->content == NULL)
				return (EXIT_FAILURE);
			return (0);
		}
		if (vars->next == NULL)
			break ;
		vars = vars->next;
	}
	return (add_exported(args[0], vars));
}
