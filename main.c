/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:41:16 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/13 16:23:16 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_main.h"

void	free_null_line_reset_signal(t_minishell *ms)
{
	free(ms->line);
	ms->line = NULL;
	g_signal = 0;
}

t_minishell	*init_ms_and_signal_setup(void)
{
	t_minishell	*ms;

	ms = init_minishell();
	if (ms == NULL)
		exit(1);
	rl_event_hook = signal_event_hook;
	signal(SIGINT, signal_handler);
	rl_catch_signals = 0;
	return (ms);
}

int	signal_rlerr_emptyl(t_minishell *ms)
{
	int	exit_status;

	if (g_signal == SIGINT)
	{
		ms->exit_status = 130;
		g_signal = 0;
		errno = 0;
		return (1);
	}
	if (ms->line == NULL && errno == 0)
	{
		exit_status = ms->exit_status;
		free_minishell(ms);
		printf("exit\n");
		exit(ms->exit_status);
	}
	if (ms->line[0] == '\0')
		return (1);
	return (0);
}

int	ctx_err_check_pipex(t_context *ctx, t_minishell *ms)
{
	if (ctx->err != NULL)
	{
		ft_putendl_fd(ctx->err, 2);
		free_ctx(ctx, ms);
		return (2);
	}
	else
		return (pipex(ctx, ms));
}

int	main(void)
{
	t_minishell	*ms;
	t_context	*ctx;

	ms = init_ms_and_signal_setup();
	while (1)
	{
		free_null_line_reset_signal(ms);
		ms->line = readline("minishell$ ");
		if (signal_rlerr_emptyl(ms) == 1)
			continue ;
		add_history(ms->line);
		if (syntax_check(ms->line) == 2)
		{
			ms->exit_status = 2;
			ft_putendl_fd("syntax error", 2);
			continue ;
		}
		ctx = parse(ft_strdup(ms->line), ms);
		if (ctx == NULL)
			continue ;
		print_ctx(ctx);
		ms->exit_status = ctx_err_check_pipex(ctx, ms);
	}
	free_minishell(ms);
}
