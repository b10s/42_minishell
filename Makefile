# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/01 16:32:54 by adrgutie          #+#    #+#              #
#    Updated: 2025/03/01 16:46:34 by adrgutie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LDLIBS		= -lreadline -lhistory
RM			= rm -fr

SRCS		= builtins/cd.c
			  builtins/echo.c
			  builtins/env.c
			  builtins/exit.c
			  builtins/export_utils.c
			  builtins/export.c
			  builtins/pwd.c
			  builtins/unset.c
			  environ_functions/free_envs.c
			  environ_functions/ft_getenv.c
			  environ_functions/ft_setenv.c
			  environ_functions/ft_unsetenv.c
			  environ_functions/get_name_value.c
			  environ_functions/init_envs.c
			  minishell/
			  minishell/
			  minishell/

