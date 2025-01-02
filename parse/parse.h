typedef **char t_cmd;

typedef struct s_context {
	commands *t_cmd;
	cmd_cnt int;
	out_red *char;
	in_red *char;
	out_fd = STDOUT;
	in_fd = STDIN;
	out_append_mode_flg int;
	here_doc_delim *char;
} t_context;
