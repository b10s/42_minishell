/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:46:18 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/19 19:18:05 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//removes the node **vars is pointing to and frees it and its content
void	update_vars(t_variable **vars, t_variable **prev)
{
	t_variable	*to_free;

	to_free = *vars;
	if (*vars == *prev)
		*vars = (*vars)->next;
	else
		(*prev)->next = (*vars)->next;
	free(to_free->content);
	free(to_free);
}

void	check_var_loop(char *args, t_variable **vars, int end_or_eq)
{
	t_variable	*prev;

	prev = NULL;
	while (*vars != NULL)
	{
		if (ft_strncmp(args, (*vars)->content, end_or_eq) == 0 \
		&& (args[end_or_eq] == '\0' || args[end_or_eq] == '=') \
		&& ((*vars)->content[end_or_eq] == '\0' || \
		(*vars)->content[end_or_eq] == '='))
		{
			update_vars(vars, &prev);
			return ;
		}
		prev = *vars;
		vars = &((*vars)->next);
	}
}

//deletes a variable or mutliple variables
int	cmd_unset(char **args, t_variable *vars)
{
	int		i;
	int		end_or_eq;
	char	*eq_pointer;

	i = 0;
	while (args[i] != NULL)
	{
		eq_pointer = ft_strchr(args[i], '=');
		if (eq_pointer != NULL)
			end_or_eq = eq_pointer - args[i];
		else
			end_or_eq = ft_strlen(args[i]);
		check_var_loop(args[i], &vars, end_or_eq);
		i++;
	}
	return (0);
}
