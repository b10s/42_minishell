/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 00:41:16 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/15 16:34:40 by adrgutie         ###   ########.fr       */
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
		ms->line = readline("minishell: ");
		ctx = parse(ms->line, ms);
		if (ctx == NULL)
			continue ;
		ms->exit_status = pipex(ctx, ms);
	}
	free_minishell(ms);
}
