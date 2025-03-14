/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:44:19 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/14 21:57:22 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../piping/pipex.h"
# include "../environ_functions/environ_functions.h"
# include "dirent.h"
# include <signal.h>

//global variable for signal
extern volatile sig_atomic_t	g_signal;

//minishell strcuture
typedef struct s_minishell
{
	char	*line;
	t_envs	*envs;
	// char	*logname;
	// char	*hostname;
	int		stdin_fd;
	int		stdout_fd;
	int		exit_status;
}	t_minishell;
//init

//free
void		free_minishell(t_minishell *ms);

//signal handler
void		signal_handler(int sigint);

//init minishell
t_minishell	*init_minishell(void);

#endif