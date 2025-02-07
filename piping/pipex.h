/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:28:56 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/07 17:42:19 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
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

# define CMD_CD 1
# define CMD_ECHO 2
# define CMD_ENV 3
# define CMD_EXIT 4
# define CMD_EXPORT 5
# define CMD_PWD 6
# define CMD_UNSET 7
# define CMD_NOT_BUILTIN 0
# define CMD_FIND_OUT -1

typedef struct s_pipex
{
	t_context	*ctx;
	int			in_fd;
	int			out_fd;
	char		*here_doc_filepath;
}	t_pipex;

//init
t_pipex	*init_spipex(t_context *ctx);

//free
void	free_spipex(t_pipex *spipex);
//close
void	close_fds(t_pipex *spipex);

//here_doc
int		put_input_in_here_doc(t_pipex *spipex);
char	*find_unique_file_name(void);
char	*get_next_line(int fd);

//cmd_utils_redirection
int		redirect_in_out(int stdinout_copy[], int in_fd, int out_fd);
int		return_in_out(int stdinout_copy[]);

//path
char	*find_cmd_path(char *cmd);

//single command
int		single_parent(int stdinout_copy, pid_t pid);

//bultin stuff
int		which_builtin(char *cmd);
int		execute_builtin(char **args, t_variable *vars, int which_builtin);

#endif