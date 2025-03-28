/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:29:13 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/29 00:17:58 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	signal_handler(int sigint)
// {
// 	(void)sigint;
// 	g_signal = 2;
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	ft_printf("\n");
// 	rl_redisplay();
// 	//ioctl(STDIN_FILENO, TIOCSTI, "p");
// 	rl_done = 1;
// }

void signal_handler(int sigint)
{
	(void)sigint;
	g_signal = 2;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_printf("\n");
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_done = 1;
}