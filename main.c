/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:41:16 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/30 18:57:15 by adrgutie         ###   ########.fr       */
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
	rl_event_hook = signal_event_hook;
	signal(SIGINT, signal_handler);
	rl_catch_signals = 0;
	while (1)
	{
		free(ms->line);
		ms->line = NULL;
		g_signal = 0;
		ms->line = readline("minishell$ ");
		if (g_signal == SIGINT)
		{
			ms->exit_status = 130;
			g_signal = 0;
			errno = 0;
			continue ;
		}
		if (ms->line == NULL && errno == 0)
		{
			free_minishell(ms);
			printf("exit\n");
			exit(ms->exit_status);
		}
		if (ms->line[0] == '\0')
			continue ;
		if (is_here_doc(ms->line) == 0)
			add_history(ms->line);
		ctx = parse(ft_strdup(ms->line), ms);
		if (ctx == NULL)
			continue ;
		print_ctx(ctx);
		if (ctx->err != NULL)
		{
			ft_putendl_fd(ctx->err, 2);
			free_ctx(ctx, ms);
			ms->exit_status = 2;
			continue ;
		}
		else
			ms->exit_status = pipex(ctx, ms);
	}
	free_minishell(ms);
}
