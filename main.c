/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:41:16 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/18 23:11:57 by adrgutie         ###   ########.fr       */
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
			exit(ms->exit_status);
		}
		ctx = parse(ms->line, ms);
		if (ctx == NULL)
			continue ;
		ms->exit_status = pipex(ctx, ms);
	}
	free_minishell(ms);
}
