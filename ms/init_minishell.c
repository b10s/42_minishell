/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:11:33 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/06 11:52:31 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_minishell(void)
{
	t_minishell	*ms;

	ms = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
	if (ms == NULL)
		return (NULL);
	ms->line = NULL;
	ms->stdin_fd = -2;
	ms->stdout_fd = -2;
	ms->exit_status = 0;
	ms->envs = init_envs();
	if (ms->envs == NULL)
		return (free_minishell(ms), NULL);
	return (ms);
}
