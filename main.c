/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:41:16 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/01 01:13:57 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_main.h"

int	main(void)
{
	t_minishell	*ms;
	t_context	*ctx;
	t_pipex		*spipex;

	ms = init_minishell();
	if (ms == NULL)
		return (EXIT_FAILURE);
	signal(SIGINT, signal_handler);
	while (1)
	{
		ms->line = readline("minishell:");
		ctx = parse(ms->line);
		if (ctx == NULL)
			return (free_minishell(ms), EXIT_FAILURE);
		ms->exit_status = pipex(ctx, ms);
	}
	free_minishell(ms);
}
