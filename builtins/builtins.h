/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:27:12 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/11 23:38:45 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"

//this global variable automatically holds the environment variables
//It allows the environment variables to be changed for the program
extern char	**environ;

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
int	echo(char **args);
int	cd(char *path);
int	pwd(void);
int	export(char **args, t_variable *vars);
int	unset(char **args, t_variable *vars);

#endif