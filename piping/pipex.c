/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:28:21 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/18 23:19:58 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	prep_ctx(t_context *ctx)
{
	int	i;

	ctx->pipe_read = -2;
	ctx->pipe_read_index = -2;
	if (ctx->cmds == NULL)
		return ;
	i = 0;
	while (ctx->cmds[i] != NULL)
	{
		ctx->cmds[i]->in_fd = -2;
		ctx->cmds[i]->out_fd = -2;
		ctx->cmds[i]->here_doc_filename = NULL;
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

int	pipeloop(int i, pid_t *pid, t_context *ctx, t_minishell *ms)
{
	int	ret;

	if (open_red_loop(ctx, ms, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (g_signal == 2)
		return (g_signal + 128);
	if (apoc_in(i, ctx, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (apoc_out(i, ctx, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ret = gen_exec(i, pid, ctx, ms);
	restore_in_out(ms);
	return (ret);
}

int	pipex(t_context *ctx, t_minishell *ms)
{
	int		i;
	int		last_status;
	pid_t	*pid;

	if (save_in_out(ms) == EXIT_FAILURE)
		return (free_ctx(ctx), EXIT_FAILURE);
	prep_ctx(ctx);
	i = 0;
	while (i < ctx->cmd_cnt)
	{
		last_status = pipeloop(i, &pid, ctx, ms);
		if (last_status == 130)
			return (waitpid(pid, NULL, 0), free_ctx(ctx), 130);
		i++;
	}
	if (ctx->cmd_cnt == 1 && \
		which_builtin(ctx->cmds[0]->cmd_with_args[0]) != CMD_NOT_BUILTIN)
		return (free_ctx(ctx), last_status);
	free_ctx(ctx);
	waitpid(pid, &last_status, 0);
	restore_inout_close(ms);
	return (status_check(last_status));
}
