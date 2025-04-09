/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:40:41 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/10 02:57:05 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all_fds_except_used(int i, t_context *ctx)
{
	int	j;

	j = 0;
	while (j < ctx->cmd_cnt && j != i)
	{
		close_set_gen(&(ctx->cmds[j]->in_fd));
		close_set_gen(&(ctx->cmds[j]->out_fd));
		j++;
	}
	close_set_gen(&(ctx->pipe_read));
}

int	execute_cmd(int i, t_context *ctx, t_minishell *ms)
{
	char	*cmd_path;
	char	**cmd_and_args;

	close_all_fds_except_used(i, ctx);
	cmd_and_args = ctx->cmds[i]->cmd_with_args;
	cmd_path = find_cmd_path(cmd_and_args[0], ms->envs);
	if (execve(cmd_path, cmd_and_args, ms->envs->env_cpy) == -1)
	{
		free(cmd_path);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

int	gen_exec(int i, t_context *ctx, t_minishell *ms)
{
	int		w_b;
	int		ret;

	w_b = which_builtin(ctx->cmds[i]->cmd_with_args[0]);
	if (ctx->cmd_cnt == 1 && w_b != CMD_NOT_BUILTIN)
		;
	else
	{
		(ctx->pid[i]) = fork();
		if ((ctx->pid[i]) == -1)
			return (perror("fork"), exit(1), EXIT_FAILURE);
	}
	if (ctx->pid[i] == 0 || ctx->pid[i] == -2)
	{
		if (w_b != CMD_NOT_BUILTIN)
			ret = execute_builtin((ctx->cmds[i]->cmd_with_args) + 1, \
													ms, ctx, w_b);
		else
			return (execute_cmd(i, ctx, ms));
		if (ctx->pid[i] == 0)
			exit(ret);
	}
	return (EXIT_SUCCESS);
}
