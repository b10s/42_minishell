/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:44:19 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/13 18:10:54 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../environ_functions/environ_functions.h"
# include "dirent.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

//global variable for signal
extern volatile sig_atomic_t	g_signal;

//minishell strcuture
typedef struct s_minishell
{
	char	*line;
	t_envs	*envs;
	int		stdin_fd;
	int		stdout_fd;
	int		exit_status;
}	t_minishell;
//init

//free
void		free_minishell(t_minishell *ms);

//signal handler
void		signal_handler(int sigint);
int			signal_event_hook(void);

//init minishell
t_minishell	*init_minishell(void);

//close
void		close_set_gen(int *fd);

//in_out_redirection
int			save_in_out(t_minishell *ms);
int			redirect_in(int in_fd);
int			redirect_out(int out_fd);
int			restore_in_out(t_minishell *ms);
int			restore_inout_close(t_minishell *ms);

//syntax check
int			syntax_check(char *line);
#endif