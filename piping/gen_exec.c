/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:40:41 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/20 18:07:39 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd(int i, t_pipex *spipex, t_minishell *ms)
{
	char	*cmd_path;
	char	*cmd_and_args;

	cmd_and_args = spipex->ctx->commands[i];
	cmd_path = find_cmd_path(cmd_and_args[0], ms->envs);
	if (execve(cmd_path, cmd_and_args, ms->envs->env_cpy) == -1)
	{
		free(cmd_path);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	gen_exec(int i, pid_t *pid, t_pipex *spipex, t_minishell *ms)
{
	int		w_b;

	pid = 0;
	w_b = which_builtin(spipex->ctx->commands[i][0]);
	if (spipex->ctx->cmd_cnt == 1 && w_b != CMD_NOT_BUILTIN)
		;
	else
	{
		(pid) = fork();
		if ((pid) == -1)
			return (CRITICAL_EXIT);
	}
	if (pid == 0)
	{
		if (w_b != CMD_NOT_BUILTIN)
			return (execute_builtin((spipex->ctx->commands[i]) + 1, \
													ms, spipex, w_b));
		else
			return (execute_cmd(i, spipex, ms));
	}
	return (EXIT_SUCCESS);
}
