/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:11:35 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/19 14:00:49 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	which_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (CMD_CD);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (CMD_ECHO);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (CMD_ENV);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (CMD_EXIT);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (CMD_EXPORT);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (CMD_PWD);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (CMD_UNSET);
	return (CMD_NOT_BUILTIN);
}

//w_b referes to the builtin
int	execute_builtin(char **args, t_minishell *ms, t_context *ctx, int w_b)
{
	if (w_b == CMD_FIND_OUT)
		w_b = which_builtin(args[0]);
	if (w_b == CMD_CD)
		return (cmd_cd(args, ms->envs));
	if (w_b == CMD_ECHO)
		return (cmd_echo(args));
	if (w_b == CMD_ENV)
		return (cmd_env(ms->envs));
	if (w_b == CMD_EXIT)
		return (cmd_exit(args, ms, ctx));
	if (w_b == CMD_EXPORT)
		return (cmd_export(args, ms->envs));
	if (w_b == CMD_PWD)
		return (cmd_pwd());
	if (w_b == CMD_UNSET)
		return (cmd_unset(args, ms->envs));
	return (EXIT_FAILURE);
}
