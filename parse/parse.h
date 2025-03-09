#include <stdio.h>
#include <stdbool.h>
#include "../libft/libft.h"

typedef struct s_context {
	char **commands;
	int cmd_cnt;
	char *out_red;
	char *in_red;
	int out_append_mode_flg;
	char *here_doc_delim;
} t_context;

t_context *init_ctx();
void free_ctx(t_context *ctx);
t_context *parse(char *line);
void print_ctx(t_context *ctx);

