/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_spipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:59:04 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/31 17:37:00 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(t_pipex *spipex)
{
	if (spipex->ctx->in_red != NULL)
		spipex->in_fd = open(spipex->ctx->in_red, O_RDONLY);
	if (spipex->ctx->out_red != NULL)
	{
		if (spipex->ctx->out_append_mode_flg == 0)
			spipex->out_fd = open(spipex->ctx->out_red, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			spipex->out_fd = open(spipex->ctx->out_red, \
			O_CREAT | O_WRONLY | O_APPEND);
		if (spipex->out_fd == -1)
			perror("open");
	}
	if (spipex->ctx->here_doc_delim != NULL)
	{
		spipex->here_doc_filepath = find_unique_file_name();
		if (spipex->here_doc_filepath == NULL)
			return (EXIT_FAILURE);
		spipex->ctx->in_red = open(spipex->here_doc_filepath, \
		O_CREAT | O_WRONLY, 0600);
	}
	if (spipex->in_fd == -1)
		perror("open");
	return (EXIT_SUCCESS);
}

t_pipex	*init_spipex(t_context *ctx)
{
	t_pipex	*spipex;

	spipex = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (spipex == NULL)
		return (free_ctx(ctx), NULL);
	spipex->ctx = ctx;
	spipex->in_fd = -2;
	spipex->out_fd = -2;
	if (open_files(spipex) == EXIT_FAILURE)
		return (free_spipex(spipex), NULL);
	return (spipex);
}
