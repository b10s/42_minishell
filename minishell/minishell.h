/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:44:19 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/08 19:02:31 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../environ_functions/environ_functions.h"
# include "dirent.h"
# include <signal.h>

//global variable for signal
volatile sig_atomic_t	g_signal = 0;

//minishell strcuture
typedef struct s_minishell
{
	char	*line;
	t_envs	*envs;
	int		stdin;
	int		stdout;
	int		exit_status;
}	t_minishell;

//free
void	free_minishell(t_minishell *ms);

#endif