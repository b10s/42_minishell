#ifndef PARSE_H
# define PARSE_H
# include <stdio.h>
# include <stdbool.h>
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

typedef struct s_red {
	char	*name;
	int		type;
}	t_red;

typedef struct s_cmd {
	char	**cmd_with_args;
	t_red	**reds;
	int		out_fd;
	int		in_fd;
	char	*here_doc_filename;
}	t_cmd;

typedef struct s_context {
	t_cmd	**cmds;
	int		cmd_cnt;
	int		pipe_read;
	int		pipe_read_index;
	char 	*err;
	int		is_fatal;
}	t_context;

t_context	*init_ctx();
void 		free_ctx(t_context *ctx);
t_context	*parse(char *line);
void		print_ctx(t_context *ctx);
char *rm_multi_spaces(char *str);
int count_single_quotes(char *str);
int count_double_quotes(char *str);
int validate_quotes(char *str);

//interpolation
char		*ft_interpolate(char *line, t_envs *envs, t_context *ctx);

# endif
