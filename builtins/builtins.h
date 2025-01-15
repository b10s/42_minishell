/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:27:12 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/14 22:50:04 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"

//this global variable automatically holds the environment variables
//It allows the environment variables to be changed for the program
extern char	**environ;

//global variable for signal
int			g_signal;

//variable linked list
//holds all variables whether exported or not
typedef struct s_variable
{
	int					exported;
	int					read_only;
	int					integer;
	char				*content;
	struct s_variable	*next;
}	t_variable;

//builtins
int	cmd_echo(char **args);
int	cmd_cd(char *path);
int	cmd_pwd(void);
int	cmd_export(char **args, t_variable *vars);
int	cmd_unset(char **args, t_variable *vars);
int	cmd_env(void);

#endif