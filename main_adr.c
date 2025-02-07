/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/06 16:25:45 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "piping/pipex.h"

//extern char **environ;

int	main(void)
{
	t_envs		*envs;
	t_variable	*tmp;
	int			i;

	envs = init_envs();
	tmp = envs->vars;
	i = 0;
	while (envs->env_cpy[i] != NULL)
	{
		ft_printf("%s\n", envs->env_cpy[i]);
		ft_printf("%s\n", tmp->name);
		ft_printf("%s\n", tmp->value);
		tmp = tmp->next;
		i++;
	}
	free_envs(envs);
}
