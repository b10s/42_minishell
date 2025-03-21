/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:28:07 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/19 18:08:09 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_in_out(t_minishell *ms)
{
	close_set_gen(&(ms->stdin_fd));
	close_set_gen(&(ms->stdout_fd));
	ms->stdin_fd = dup(STDIN_FILENO);
	if (ms->stdin_fd == -1)
		return (EXIT_FAILURE);
	ms->stdout_fd = dup(STDOUT_FILENO);
	if (ms->stdout_fd == -1)
	{
		close_set_gen(&(ms->stdin_fd));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	restore_in_out(t_minishell *ms)
{
	if (ms->stdin_fd < 0)
		;
	else if (dup2(ms->stdin_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	if (ms->stdout_fd < 0)
		;
	else if (dup2(ms->stdout_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	restore_inout_close(t_minishell *ms)
{
	if (restore_in_out(ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close_set_gen(&(ms->stdin_fd));
	close_set_gen(&(ms->stdout_fd));
	return (EXIT_SUCCESS);
}

int	redirect_in(int in_fd, t_minishell *ms)
{
	if (in_fd >= 0)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close_set_gen(&in_fd);
			return (restore_inout_close(ms), EXIT_FAILURE);
		}
		close_set_gen(&in_fd);
	}
	return (EXIT_SUCCESS);
}

int	redirect_out(int out_fd, t_minishell *ms)
{
	if (out_fd >= 0)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close_set_gen(&out_fd);
			return (restore_inout_close(ms), EXIT_FAILURE);
		}
	}
	close_set_gen(&out_fd);
	return (EXIT_SUCCESS);
}
