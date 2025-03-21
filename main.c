/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:41:16 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/21 22:11:24 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_main.h"

int	main(void)
{
	t_minishell	*ms;
	t_context	*ctx;

	ms = init_minishell();
	if (ms == NULL)
		return (EXIT_FAILURE);
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	while (1)
	{
		g_signal = 0;
		ms->line = readline("minishell: ");
		if (g_signal == 2)
		{
			ms->exit_status = 130;
			g_signal = 0;
			errno = 0;
			continue ;
		}
		if (ms->line == NULL && errno == 0)
		{
			free_minishell(ms);
			printf("\n");
			exit(ms->exit_status);
		}
		ctx = parse(ft_strdup(ms->line), ms);
		if (ctx == NULL)
			continue ;
		print_ctx(ctx);
		ms->exit_status = pipex(ctx, ms);
		free(ms->line);
		ms->line = NULL;
	}
	free_minishell(ms);
}
