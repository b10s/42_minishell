/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/24 20:51:13 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"
#include "libft/libft.h"

void	signal_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\nSIGINT received!\n", 18);
	write(STDOUT_FILENO, "restarting sleep\n", 18);
	sleep(10);
}

int	main(void)
{
	signal(SIGINT, signal_handler);
	printf("Sleeping for 10 seconds... Press Ctrl-C\n");
	sleep(10);
	printf("Sleep finished (if not interrupted).\n");
}
