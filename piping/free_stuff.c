/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 00:54:36 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/18 01:25:29 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int p[])
{
	close_set_gen(&(p[0]));
	close_set_gen(&(p[1]));
}

void	close_fds(t_pipex *spipex)
{
	close_set_gen(&(spipex->in_fd));
	close_set_gen(&(spipex->out_fd));
	close_set_gen(&(spipex->curin));
	close_set_gen(&(spipex->curout));
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
