/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:56:47 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/18 23:41:23 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <errno.h>

void	free_reds(t_cmd *cmd)
{
	int	i;

	if (cmd->reds == NULL)
		return ;
	i = 0;
	while (cmd->reds[i] != NULL)
	{
		free(cmd->reds[i]->fname_or_delim);
		i++;
	}
	free(cmd->reds);
}

void	free_cmds_loop(t_context *ctx)
{
	int	i;

	i = 0;
	while (ctx->cmds[i] != NULL)
	{
		free_reds(ctx->cmds[i]);
		free_split(ctx->cmds[i]->cmd_with_args);
		close_set_gen(&(ctx->cmds[i]->in_fd));
		close_set_gen(&(ctx->cmds[i]->out_fd));
		if (ctx->cmds[i]->here_doc_filename != NULL)
		{
			unlink(ctx->cmds[i]->here_doc_filename);
			free(ctx->cmds[i]->here_doc_filename);
		}
		free(ctx->cmds[i]);
		i++;
	}
	free(ctx->cmds);
}

void	free_ctx(t_context *ctx, t_minishell *ms)
{
	save_in_out(ms);
	if (ctx == NULL)
		return (restore_inout_close(ms), (void)0);
	else if (ctx->cmds != NULL)
		free_cmds_loop(ctx);
	close_set_gen(&(ctx->pipe_read));
	free(ctx);
	restore_inout_close(ms);
	errno = 0;
}
