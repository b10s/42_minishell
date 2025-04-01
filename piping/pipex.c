/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:28:21 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/01 13:48:47 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	prep_ctx(t_context *ctx)
{
	int	i;

	ctx->pipe_read = -2;
	ctx->pipe_read_index = -2;
	if (ctx->cmds == NULL)
		exit(1);
	ctx->pid = (pid_t *)ft_calloc(ctx->cmd_cnt, sizeof(pid_t));
	if (ctx->pid == NULL)
		exit(1);
	i = 0;
	while (ctx->cmds[i] != NULL)
	{
		ctx->cmds[i]->in_fd = -2;
		ctx->cmds[i]->out_fd = -2;
		ctx->cmds[i]->here_doc_filename = NULL;
		ctx->pid[i] = -2;
		i++;
	}
	return ;
}

int	status_check(int last_status)
{
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (EXIT_FAILURE);
}

int	pipeloop(int i, t_context *ctx, t_minishell *ms)
{
	int	ret;

	ret = 0;
	if (open_red_loop(ctx, ms, i) == EXIT_FAILURE)
	{
		if (g_signal == 2)
			return (restore_inout_close(ms), g_signal + 128);
		return (EXIT_FAILURE);
	}
	if (apoc_in(i, ctx, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (apoc_out(i, ctx, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ctx->cmds[i]->cmd_with_args[0] != NULL)
		ret = gen_exec(i, ctx, ms);
	restore_in_out(ms);
	return (ret);
}

void	wait_loop(t_context *ctx, int *last_status)
{
	int	i;
	int	status;

	i = 0;
	while (i < ctx->cmd_cnt)
	{
		if (ctx->pid[i] > -1)
		{
			if (i == (ctx->cmd_cnt - 1))
				waitpid(ctx->pid[i], &status, 0);
			else
				waitpid(ctx->pid[i], NULL, 0);
		}
		i++;
	}
	if (ctx->pid[i - 1] > -1)
		*last_status = status_check(status);
}

int	pipex(t_context *ctx, t_minishell *ms)
{
	int		i;
	int		last_status;

	if (save_in_out(ms) == EXIT_FAILURE)
		return (free_ctx(ctx, ms), EXIT_FAILURE);
	prep_ctx(ctx);
	i = 0;
	while (i < ctx->cmd_cnt)
	{
		last_status = pipeloop(i, ctx, ms);
		if (last_status == 130)
			return (wait_loop(ctx, &last_status), free_ctx(ctx, ms), 130);
		i++;
	}
	wait_loop(ctx, &last_status);
	if (ctx->cmds[i - 1]->cmd_with_args[0] == NULL)
		return (free_ctx(ctx, ms), restore_inout_close(ms), 0);
	free_ctx(ctx, ms);
	restore_inout_close(ms);
	return (last_status);
}
