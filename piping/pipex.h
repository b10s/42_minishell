/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:28:56 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/12 21:02:05 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../ms/minishell.h"
# include "../parse/parse.h"
# include "../builtins/builtins.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WRITE 1
# define READ 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define CLEAR_MEM -10

# define CRITICAL_EXIT 2

//close
void	close_pipe(int p[]);

//here_doc
int		put_input_in_here_doc(char *limiter, t_cmd *cmd, t_minishell *ms);
char	*find_unique_file_name(void);

//path
char	*find_cmd_path(char *cmd, t_envs *envs);

//bultin stuff
int		which_builtin(char *cmd);
int		execute_builtin(char **args, t_minishell *ms, t_context *ctx, int w_b);

//open
int		open_in(char *name, t_cmd *cmd);
int		open_out(char *name, t_cmd *cmd);
int		open_out_append(char *name, t_cmd *cmd);
int		open_here_doc(char *limiter, t_cmd *cmd, t_minishell *ms);
//bigboy open
int		open_red_loop(t_context *ctx, t_minishell *ms, int i);
//red_apocalypse
int		apoc_in(int i, t_context *ctx, t_minishell *ms);
int		apoc_out(int i, t_context *ctx, t_minishell *ms);
//pipex
int		gen_exec(int i, t_context *ctx, t_minishell *ms);
//the one
int		pipex(t_context *ctx, t_minishell *ms);

//error msg
void	put_cmd_error(char *cmd, char *error_msg);

#endif