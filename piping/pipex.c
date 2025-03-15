/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:28:21 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/15 19:23:48 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	prep_ctx_prep_ms(t_context *ctx, t_minishell *ms)
{
	int	i;

	if (save_in_out(ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ctx->pipe_read = -2;
	i = 0;
	while (i < ctx->cmd_cnt)
	{
		ctx->cmds[i]->in_fd = -2;
		ctx->cmds[i]->out_fd = -2;
		ctx->cmds[i]->here_doc_filename = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	status_check(int last_status)
{
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (EXIT_FAILURE);
}

int	close_pipe_exit_failure(int	*pipe_read, int *pipe_write)
{
	close_set_gen(pipe_read);
	close_set_gen(pipe_write);
	return (EXIT_FAILURE);
}

int	pipeloop(int i, pid_t *pid, t_context *ctx, t_minishell *ms)
{
	int		pipe_fd[2];
	int		in;
	int		out;
	int		ret;

	if (open_red_loop(ctx, ms, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ctx->cmds[i]->in_fd > -1)
		in = ctx->cmds[i]->in_fd;
	else if (ctx->pipe_read > -1)
		in = ctx->pipe_read;
	else
	{
		in = dup(ms->stdin_fd);
		if (in == -1)
			return (EXIT_FAILURE);
	}
	if (redirect_in(in, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close_set_gen(&(ctx->pipe_read));
	if (ctx->cmds[i]->out_fd > -1)
		out = ctx->cmds[i]->out_fd;
	else
	{
		if (pipe(pipe_fd) == -1)
			return (EXIT_FAILURE);
		out = pipe_fd[WRITE];
		ctx->pipe_read = pipe_fd[READ];
	}
	if (redirect_out(out, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ret = gen_exec(i, pid, ctx, ms);
	if (ret == CRITICAL_EXIT)
		return (close_set_gen(&(ctx->pipe_read)), EXIT_FAILURE);
	return (ret);
}

int	pipex(t_context *ctx, t_minishell *ms)
{
	int		i;
	int		last_status;
	pid_t	*pid;

	if (prep_ctx_prep_ms(ctx, ms) == EXIT_FAILURE)
		return (free_ctx(ctx), EXIT_FAILURE);
	i = 0;
	while (i < ctx->cmd_cnt)
	{
		last_status = pipeloop(i, &pid, ctx, ms);
		if (last_status == CRITICAL_EXIT)
			return (free_ctx(ctx), EXIT_FAILURE);
		i++;
	}
	if (ctx->cmd_cnt == 1 && \
		which_builtin(ctx->cmds[0]->cmd_with_args[0]) != CMD_NOT_BUILTIN)
		return (free_ctx(ctx), last_status);
	free_ctx(ctx);
	waitpid(pid, &last_status, NULL);
	restore_inout_close(ms);
	return (status_check(last_status));
}
