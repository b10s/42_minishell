/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_red_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:11:01 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/19 14:09:08 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_type(t_cmd *cmd, t_red *red, t_minishell *ms)
{
	if (red->type == IN)
		return (open_in(red->fname_or_delim, cmd));
	if (red->type == OUT)
		return (open_out(red->fname_or_delim, cmd));
	if (red->type == OUT_APPEND)
		return (open_out_append(red->fname_or_delim, cmd));
	if (red->type == HERE_DOC)
		return (open_here_doc(red->fname_or_delim, cmd, ms));
	return (EXIT_FAILURE);
}

//loop that opens all the files in a cmd structure, it will also
//redirect the input and output to the last valid file
//if a file fails to open, then the command will not be executed
//and the next files will not be opened
int	open_red_loop(t_context *ctx, t_minishell *ms, int i)
{
	int	j;

	j = 0;
	while (ctx->cmds[i]->reds[j] != NULL)
	{
		if (open_type(ctx->cmds[i], ctx->cmds[i]->reds[j], ms) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}