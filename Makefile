# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/01 16:32:54 by adrgutie          #+#    #+#              #
#    Updated: 2025/03/18 22:43:05 by adrgutie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
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
			  parse/parse.c \
			  piping/execute_builtin.c \
			  piping/find_cmd_path.c \
			  piping/free_stuff.c \
			  piping/gen_exec.c \
			  piping/here_doc_fine_name.c \
			  piping/here_doc.c \
			  piping/init_spipex.c \
			  piping/pipex.c 
			  

OBJS		= $(SRCS:.c=.o)

INCLUDES = -I. -Ienviron_functions -Iminishell -Iparse -Ipiping -Ilibft

%.o: %.C
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONEY : all clean fclean re bonus



