/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:57:34 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/04 22:47:55 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	which_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd", 3) == 0)
		return (CMD_CD);
	if (ft_strcmp(cmd, "echo", 5) == 0)
		return (CMD_ECHO);
	if (ft_strcmp(cmd, "env", 4) == 0)
		return (CMD_ENV);
	if (ft_strcmp(cmd, "exit", 5) == 0)
		return (CMD_EXIT);
	if (ft_strcmp(cmd, "export", 7) == 0)
		return (CMD_EXPORT);
	if (ft_strcmp(cmd, "pwd", 4) == 0)
		return (CMD_PWD);
	if (ft_strcmp(cmd, "unset", 6) == 0)
		return (CMD_UNSET);
	return (CMD_NOT_BUILTIN);
}

int	execute_builtin(char **args, t_variable *vars, int w_b)
{
	if (w_b == CMD_FIND_OUT)
		w_b = which_builtin(args[0]);
	if (w_b == CMD_CD)
		return (cmd_cd(args[0]));
	if (w_b == CMD_ECHO)
		return (cmd_echo(args));
	if (w_b == CMD_ENV)
		return (cmd_env());
	if (w_b == CMD_EXIT)
		return (cmd_exit(args));
	if (w_b == CMD_EXPORT)
		return (cmd_export(args, vars));
	if (w_b == CMD_PWD)
		return (cmd_pwd());
	if (w_b == CMD_UNSET)
		return (cmd_unset(args, vars));
	return (EXIT_FAILURE);
}

static int	red_execute_builtin(t_pipex *spipex, t_variable *vars, int w_b)
{
	int	stdinout_copy[2];
	int	signal;

	stdinout_copy[0] = -1;
	stdinout_copy[1] = -1;
	if (redirect_in_out(stdinout_copy, spipex->in_fd, spipex->out_fd) \
		== EXIT_FAILURE)
		return (EXIT_FAILURE);
	g_signal = execute_builtin(spipex->ctx->commands[0], vars, w_b);
	if (return_in_out(stdinout_copy) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute_single_cmd(t_pipex *spipex)
{
	pid_t	pid;
	int		stdinout_copy[2];
	char	*cmd_path;

	stdinout_copy[0] = -1;
	stdinout_copy[1] = -1;
	if (redirect_in_out(stdinout_copy, spipex->in_fd, spipex->out_fd) \
		== EXIT_FAILURE)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (return_in_out(stdinout_copy), EXIT_FAILURE);
	if (pid == 0)
	{
		cmd_path = find_cmd_path(spipex->ctx->commands[0][0]);
		if (execve(cmd_path, spipex->ctx->commands[0], environ) == -1)
		{
			perror("execve");
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else
		return (single_parent(stdinout_copy, pid));
}

int	execute_single(t_pipex *spipex, t_variable *vars)
{
	int		w_b;
	int		status;

	w_b = which_builtin(spipex->ctx->commands[0][0]);
	if (w_b != CMD_NOT_BUILTIN)
	{
		status = red_execute_builtin(spipex, vars, w_b);
		if (g_signal != 0)
			return (g_signal + 128);
		else
			return (status);
	}
	else
		return (execute_single_cmd(spipex));
}
