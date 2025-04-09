# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/01 16:32:54 by adrgutie          #+#    #+#              #
#    Updated: 2025/04/06 20:49:11 by adrgutie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LDLIBS		= -lreadline -lhistory
RM			= rm -fr

SRCS		= main.c \
			  builtins/cd.c \
			  builtins/echo.c \
			  builtins/env.c \
			  builtins/exit.c \
			  builtins/export_utils.c \
			  builtins/export.c \
			  builtins/pwd.c \
			  builtins/unset.c \
			  environ_functions/free_envs.c \
			  environ_functions/ft_getenv.c \
			  environ_functions/ft_setenv.c \
			  environ_functions/ft_unsetenv.c \
			  environ_functions/get_name_value.c \
			  environ_functions/init_envs.c \
			  ms/free_minishell.c \
			  ms/init_minishell.c \
			  ms/signal_handling.c \
			  ms/redirect_in_out.c \
			  ms/here_doc_check.c \
			  ms/syntax_error.c \
			  parse/parse.c \
			  parse/free_ctx.c \
			  parse/interp_and_clean_quotes.c \
			  parse/remove_a_layer_of_quotes.c \
			  parse/ft_interpolate.c \
			  parse/add_word_redir.c \
			  parse/misc.c \
			  parse/utils.c \
			  parse/token.c \
			  parse/remove_spaces.c \
			  parse/redirections.c \
			  piping/execute_builtin.c \
			  piping/find_cmd_path.c \
			  piping/gen_exec.c \
			  piping/here_doc_find_name.c \
			  piping/here_doc.c \
			  piping/open_red_loop.c \
			  piping/open.c \
			  piping/pipex.c \
			  piping/red_apocalypse.c
			  

OBJS		= $(SRCS:.c=.o)

INCLUDES = -I. -Ienviron_functions -Iminishell -Iparse -Ipiping -Ilibft

%.o: %.C
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS) -Llibft -lft

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONEY : all clean fclean re bonus



