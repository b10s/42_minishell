/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:27:12 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/12 23:55:26 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../environ_functions/environ_functions.h"
# include "../minishell/minishell.h"
# include "../piping/pipex.h"

//builtins
int	cmd_echo(char **args);
int	cmd_cd(char *path);
int	cmd_pwd(void);
int	cmd_export(char **args, t_envs *envs);
int	cmd_unset(char **args, t_variable *vars);
int	cmd_env(t_envs *envs);
int	cmd_exit(char **args, t_minishell *ms, t_pipex *spipex);

//check variable argument for export
int	valid_var_check(char *v_n);

#endif