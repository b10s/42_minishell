/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/26 00:40:55 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"
#include "libft/libft.h"
#include "readline/readline.h"
#include "environ_functions/environ_functions.h"
#include "builtins/builtins.h"

void	signal_handler(int signo)
{
	(void)signo;
	ft_printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int	main(void)
{
	char	*line;
	t_envs	*envs;

	envs = init_envs();
	ft_setenv("HOSTNAME", "hostname", 1, envs);
	signal(SIGINT, signal_handler);
	while (1)
	{
		printf("readline... Press Ctrl-C\n");
		ft_printf("%s@%s:%s$ ", ft_getenv("USER", envs), ft_getenv("HOSTNAME", envs), ft_getenv("PWD", envs));
		line = readline("now readline: ");
		if (line[0] == 'd')
			break ;
		free(line);
	}
	free(line);
	free_envs(envs);
}
