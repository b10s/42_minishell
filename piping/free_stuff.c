/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:54:36 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/31 01:41:34 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	close_fds(t_pipex *spipex)
{
	if (spipex->ctx->in_red != NULL || spipex->here_doc_filepath != NULL)
	{
		if (spipex->in_fd != -1)
			close(spipex->in_fd);
		spipex->in_fd = -1;
	}
		
	if (spipex->ctx->out_red != NULL)
	{
		if (spipex->out_fd != -1)
			close(spipex->out_fd);
		spipex->out_fd = -1;
	}
}

void	free_spipex(t_pipex *spipex)
{
	if (spipex == NULL)
		return ;
	close_fds(spipex);
	if (spipex->here_doc_filepath != NULL)
	{
		if (unlink(spipex->here_doc_filepath) == -1)
			perror("unlink");
	}
	free(spipex->here_doc_filepath);
	free_ctx(spipex->ctx);
	free(spipex);
}
