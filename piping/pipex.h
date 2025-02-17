/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:28:56 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/18 01:23:00 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../minishell/minishell.h"
# include "../parse/parse.h"
# include "../builtins/builtins.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# define WRITE 1
# define READ 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define CLEAR_MEM -10

typedef struct s_pipex
{
	t_context	*ctx;
	int			in_fd;
	int			out_fd;
	int			curin;
	int			curout;
	char		*here_doc_filepath;
}	t_pipex;

//init
t_pipex	*init_spipex(t_context *ctx);

//free
void	free_spipex(t_pipex *spipex);
//close
void	close_fds(t_pipex *spipex);
int		close_set_gen(int *fd);
void	close_pipe(int p[]);

//here_doc
int		put_input_in_here_doc(t_pipex *spipex);
char	*find_unique_file_name(void);
char	*get_next_line(int fd);

//in_out_redirection
int		save_in_out(t_minishell *ms);
int		redirect_in(int in_fd, t_minishell *ms);
int		redirect_out(int out_fd, t_minishell *ms);
int		restore_in_out(t_minishell *ms);
int		restore_inout_close(t_minishell *ms);

//path
char	*find_cmd_path(char *cmd);

//bultin stuff
int		which_builtin(char *cmd);
int		execute_builtin(char **args, t_minishell *ms, \
			t_pipex *spipex, int which_builtin);


#endif