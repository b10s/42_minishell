/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:54:36 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/22 02:05:56 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_pipex *spipex)
{
	if (spipex->ctx->in_red != NULL || spipex->here_doc_filepath != NULL)
		close(spipex->in_fd);
	if (spipex->ctx->out_red != NULL)
		close(spipex->out_fd);
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
