/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:28:21 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/25 18:22:00 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	red_hel(int i, t_pipex *spipex, t_minishell *ms)
{
	if (i == 0 && \
		(spipex->ctx->in_red != NULL || spipex->here_doc_filepath == NULL))
		spipex->curin = spipex->in_fd;
	else
		spipex->curin = dup(ms->stdin_fd);
	if (spipex->curin < 0)
		return (EXIT_FAILURE);
	if (redirect_in(spipex->curin, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (i == spipex->ctx->cmd_cnt - 1)
	{
		if (spipex->ctx->out_red != NULL)
			spipex->curout = spipex->out_fd;
		else
			spipex->curout = dup(ms->stdout_fd);
		if (spipex->curout < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	pipeloop(int i, pid_t *pid, t_pipex *spipex, t_minishell *ms)
{
	int		pipe_fd[2];
	int		ret;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (red_hel(i, spipex, ms) == EXIT_FAILURE)
		return (CRITICAL_EXIT);
	if (i < spipex->ctx->cmd_cnt - 1)
	{
		if (pipe(pipe_fd) == -1)
			return (CRITICAL_EXIT);
		spipex->curin = pipe_fd[0];
		spipex->curout = pipe_fd[1];
	}
	if (redirect_out(spipex->curout, ms) == EXIT_FAILURE)
		return (close_pipe(pipe_fd), CRITICAL_EXIT);
	ret = gen_exec(i, &pid, spipex, ms);
	restore_in_out(ms);
	return (ret);
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
	t_pipex	*spipex;
	int		i;
	int		last_status;
	pid_t	*pid;

	spipex = init_spipex(ctx);
	if (spipex == NULL)
		return (EXIT_FAILURE);
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
