/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:29:13 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/24 20:46:38 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\nSIGINT received!\n", 18);
}

int	main(void)
{
	signal(SIGINT, signal_handler);
	printf("Sleeping for 10 seconds... Press Ctrl-C\n");
	sleep(10);
	printf("Sleep finished (if not interrupted).\n");
}
