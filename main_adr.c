/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/23 19:45:38 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "piping/pipex.h"

//extern char **environ;

int	main(void)
{
	int		in;
	char	*line;

	in = open("wow", O_CREAT | O_WRONLY, 0644);
	write(in, "die die die\n", 12);
	close(in);
	in = open("wow", O_RDONLY);
	while (1)
	{
		line = get_next_line(in);
		printf("%s", line);
		if (line == NULL)
		{
			printf("\n");
			break ;
		}
		free(line);
	}
	return (0);
}
