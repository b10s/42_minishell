/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:27:12 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/15 13:38:54 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../environ_functions/environ_functions.h"
# include "../minishell/minishell.h"
# include "../piping/pipex.h"

# define CMD_CD 1
# define CMD_ECHO 2
# define CMD_ENV 3
# define CMD_EXIT 4
# define CMD_EXPORT 5
# define CMD_PWD 6
# define CMD_UNSET 7
# define CMD_NOT_BUILTIN 0
# define CMD_FIND_OUT -1

//builtins
int	cmd_echo(char **args);
int	cmd_cd(char **args, t_envs *envs);
int	cmd_pwd(void);
int	cmd_export(char **args, t_envs *envs);
int	cmd_unset(char **args, t_envs *envs);
int	cmd_env(t_envs *envs);
int	cmd_exit(char **args, t_minishell *ms, t_pipex *spipex);

//check variable argument for export
int	valid_var_check(char *v_n, int which_cmd);

#endif