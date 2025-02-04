/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:37:04 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/31 17:43:39 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	close_stdinout_copy(int stdinout_copy[])
{
	if (stdinout_copy[0] != -1)
		close(stdinout_copy[0]);
	if (stdinout_copy[1] != -1)
		close(stdinout_copy[1]);
}

int	red_dup2(int stdinout_copy[], int in_fd, int out_fd)
{
	if (in_fd != -2)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			close_stdinout_copy(stdinout_copy);
			return (perror("dup2"), EXIT_FAILURE);
		}
		close(in_fd);
	}
	if (out_fd != -2)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			dup2(stdinout_copy[0], STDIN_FILENO);
			close_stdinout_copy(stdinout_copy);
			return (perror("dup2"), EXIT_FAILURE);
		}
		close(out_fd);
	}
	return (EXIT_SUCCESS);
}

int	redirect_in_out(int stdinout_copy[], int in_fd, int out_fd)
{
	stdinout_copy[0] = dup(STDIN_FILENO);
	if (stdinout_copy[0] == -1)
		return (perror("dup"), EXIT_FAILURE);
	stdinout_copy[1] = dup(STDOUT_FILENO);
	if (stdinout_copy[1] == -1)
	{
		close(stdinout_copy[0]);
		return (perror("dup"), EXIT_FAILURE);
	}
	if (red_dup2(stdinout_copy, in_fd, out_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	return_in_out(int stdinout_copy[])
{
	if (dup2(stdinout_copy[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (close_stdinout_copy(stdinout_copy), EXIT_FAILURE);
	}
	if (dup2(stdinout_copy[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (close_stdinout_copy(stdinout_copy), EXIT_FAILURE);
	}
	close_stdinout_copy(stdinout_copy);
	return (EXIT_SUCCESS);
}
