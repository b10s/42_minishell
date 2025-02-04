/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:27:12 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/05 00:36:38 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../environ_functions/environ_functions.h"

# include "dirent.h"
# include <signal.h>

//global variable for signal
volatile sig_atomic_t	g_signal = 0;

//builtins
int	cmd_echo(char **args);
int	cmd_cd(char *path);
int	cmd_pwd(void);
int	cmd_export(char **args, t_variable *vars);
int	cmd_unset(char **args, t_variable *vars);
int	cmd_env(void);
int	cmd_exit(char **args);

#endif