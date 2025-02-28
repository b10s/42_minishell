/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:00:23 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/28 18:17:15 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//will close an fd, and set it equal to -1 signifying that it is closed
int	close_set_gen(int *fd)
{
	if (*fd > -1)
		close(*fd);
	*fd = -1;
}

void	free_minishell(t_minishell *ms)
{
	if (ms == NULL)
		return ;
	close_set_gen(&(ms->stdin_fd));
	close_set_get(&(ms->stdout_fd));
	free_envs(ms->envs);
	free(ms->line);
	free(ms->hostname);
	free(ms);
}
