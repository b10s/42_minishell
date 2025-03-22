/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_apocalypse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:44:21 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/23 03:13:11 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	apoc_in(int i, t_context *ctx, t_minishell *ms)
{
	int	in;

	if (ctx->cmds[i]->in_fd > -1)
		in = ctx->cmds[i]->in_fd;
	else if (ctx->pipe_read > -1 && ctx->pipe_read_index == i)
		in = ctx->pipe_read;
	else
	{
		in = dup(ms->stdin_fd);
		if (in == -1)
			exit(1);
	}
	redirect_in(in);
	close_set_gen(&(ctx->pipe_read));
	return (EXIT_SUCCESS);
}

int	apoc_out(int i, t_context *ctx, t_minishell *ms)
{
	int	out;
	int	pipe_fd[2];

	if (ctx->cmds[i]->out_fd > -1)
		out = ctx->cmds[i]->out_fd;
	else if (i < ctx->cmd_cnt - 1)
	{
		if (pipe(pipe_fd) == -1)
			exit(1);
		out = pipe_fd[WRITE];
		ctx->pipe_read = pipe_fd[READ];
		ctx->pipe_read_index = i + 1;
	}
	else
	{
		out = dup(ms->stdout_fd);
		if (out == -1)
			exit(1);
	}
	redirect_out(out);
	return (EXIT_SUCCESS);
}
