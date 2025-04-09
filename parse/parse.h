/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:28:31 by aenshin           #+#    #+#             */
/*   Updated: 2025/03/28 18:31:57 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include "../environ_functions/environ_functions.h"
# include "../ms/minishell.h"

// typedef char **t_cmd;

// typedef struct s_context {
// 	t_cmd *commands;
// 	int cmd_cnt;
// 	char *out_red;
// 	char *in_red;
// 	int out_append_mode_flg;
// 	char *here_doc_delim;
// } t_context;

# define IN 0
# define HERE_DOC 1
# define OUT 2
# define OUT_APPEND 3
# define QUOTES_ERR "unclosed quotes error, try again"
# define RED_CNT 0
# define RED_MAX 1
# define WRD_CNT 2
# define WRD_MAX 3

typedef struct s_token
{
	char	*beg;
	int		len;
	char	*tok;
}	t_token;

typedef struct s_red
{
	char	*fname_or_delim;
	int		type;
}	t_red;

typedef struct s_cmd
{
	char	**cmd_with_args;
	t_red	**reds;
	int		out_fd;
	int		in_fd;
	char	*here_doc_filename;
}	t_cmd;

typedef struct s_context
{
	t_cmd	**cmds;
	int		cmd_cnt;
	int		pipe_read;
	int		pipe_read_index;
	pid_t	*pid;
	char	*err;
}	t_context;

t_context	*init_ctx(void);
t_context	*parse(char *line, t_minishell *ms);
void		print_ctx(t_context *ctx);
char		*rm_multi_spaces(char *str);
int			count_single_quotes(char *str);
int			count_double_quotes(char *str);
int			validate_quotes(char *str);
size_t		count_spaces_to_rm(char *str);
int			count_pipes(char *s);
char		**split_pipes(char *s);
int			cmd_size_till_pipe(char *cmd);
char		*rm_spaces_near_redir(char *str);
size_t		count_spaces_to_rm_near_redir(char *str);
t_token		*get_next_token(char *str);
int			token_allowed_chars(char c);
void		add_word(char ***words, char *w, int *wrd_cnt, int *wrd_max);
void		print_ctx(t_context *ctx);
void		add_reds(t_red ***reds, t_red *r, int *red_cnt, int *red_max);
int			count_commands(char **cmds);
char		*remove_spaces(char *line);
void		parse_commands(t_context *ctx, char **commands);
int			parse_single_cmd(char *pos, int cmd_idx, int a[4], t_context *ctx);
t_red		*get_redirection(char **pos_in_cmd, int skip, int type);
void		free_red(t_red *red);
int			parse_reds(t_red ***reds, char **pos, int *red_cnt, int *red_max);
int			parse_words(char ***wrds, char **pos, int *wrd_cnt, int *wrd_max);

//interpolation
char		*ft_interpolate(char *line, t_minishell *ms, int quote_check);
//remove a layer of quotes
char		*remove_a_layer_of_quotes(char *str);
//function that interpolates and removes a quote layer from cmds, args, and reds
int			interp_remquotelayer(t_context *ctx, t_minishell *ms);
//free_ctx
void		free_ctx(t_context *ctx, t_minishell *ms);
#endif
