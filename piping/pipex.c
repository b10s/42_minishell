/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:28:21 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/15 15:52:49 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipeloop(int i, pid_t *pid, t_pipex *spipex, t_minishell *ms)
{
	int		pipe_fd[2];
	int		ret;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
}

int	status_check(int last_status)
{
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (EXIT_FAILURE);
}

int	pipex(t_context *ctx, t_minishell *ms)
{
	int		i;
	int		last_status;
	pid_t	*pid;

	if (save_in_out(ms) == EXIT_FAILURE)
		return (free_spipex(spipex), EXIT_FAILURE);
	i = 0;
	while (i < spipex->ctx->cmd_cnt)
	{
		last_status = pipeloop(i, &pid, spipex, ms);
		if (last_status == CRITICAL_EXIT)
			return (free(spipex), EXIT_FAILURE);
		i++;
	}
	free_spipex(spipex);
	if (spipex->ctx->cmd_cnt == 1 && \
		which_builtin(spipex->ctx->commands[0][0] != CMD_NOT_BUILTIN))
		return (last_status);
	waitpid(pid, &last_status, NULL);
	restore_inout_close(ms);
	return (status_check(last_status));
}
