/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:57:55 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/14 21:48:18 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_in(char *name)
{
	int	fd;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		perror("open");
	return (fd);
}

int	open_out(char *name)
{
	int fd;
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror("open");
	return (fd);
}

int	open_out_append(char *name)
{
	int fd;
	fd = open(name, O_CREAT | O_WRONLY | O_APPEND);
	if (fd == -1)
		perror("open");
	return (fd);
}