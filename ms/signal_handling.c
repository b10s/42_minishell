/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:29:13 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/13 18:10:50 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_event_hook(void)
{
	return (EXIT_SUCCESS);
}

void	signal_handler(int sigint)
{
	(void)sigint;
	g_signal = SIGINT;
	rl_replace_line("^C", 0);
	rl_redisplay();
	rl_done = 1;
}
