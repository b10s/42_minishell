/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:04:32 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/05 00:35:58 by adrgutie         ###   ########.fr       */
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
	int					read_only;
	int					integer;
	char				*content;
	struct s_variable	*next;
}	t_variable;

//structure to hold the copy of the environ variable
//and the t_variable linked list
typedef struct s_envs
{
	char		**env_cpy;
	t_variable	vars;
}	t_envs;

#endif