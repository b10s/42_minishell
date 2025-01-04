#include <stdio.h>

typedef char ** t_cmd;

typedef struct s_context {
	t_cmd *commands;
	int cmd_cnt;
	char *out_red;
	char *in_red;
	FILE *out_fd;
	FILE *in_fd;
	int out_append_mode_flg;
	char *here_doc_delim;
} t_context;

t_context *init_ctx();
void free_ctx(t_context *ctx);
int parse(char *line, t_context *ctx);

