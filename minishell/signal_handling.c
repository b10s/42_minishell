/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:29:13 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/25 23:45:51 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline/readline.h"

void	signal_handler(int signo)
{
	(void)signo;
	printf("\n");
}

int	main(void)
{
	char	*line;

	signal(SIGINT, signal_handler);
	while (1)
	{
		printf("readline... Press Ctrl-C\n");
		line = readline("");
		if (line[0] == 'd')
			break ;
	}
	free(line);
}
