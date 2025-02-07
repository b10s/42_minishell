/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:04:32 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/06 15:12:50 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_FUNCTIONS_H
# define ENVIRON_FUNCTIONS_H

# include "../libft/libft.h"

//this global variable automatically holds the environment variables
extern char				**environ;

//variable linked list
//holds all variables whether exported or not
typedef struct s_variable
{
	int					exported;
	char				*name;
	char				*value;
	struct s_variable	*next;
}	t_variable;

//structure to hold the copy of the environ variable
//and the t_variable linked list
typedef struct s_envs
{
	char		**env_cpy;
	t_variable	*vars;
}	t_envs;

//free
void	free_envs(t_envs *envs);

//test
char	*get_name(char *name_value);
char	*get_value(char *name_value);

//init
int		init_vars(t_envs *envs);
t_envs	*init_envs(void);

#endif