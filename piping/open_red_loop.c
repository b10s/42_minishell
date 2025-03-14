/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_red_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:11:01 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/15 02:45:20 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_type(t_context *ctx, t_cmd *cmd, t_red *red)
{
	if (spipex->ctx->in_red != NULL)
		spipex->in_fd = open(spipex->ctx->in_red, O_RDONLY);
}
//loop that opens all the files in a cmd structure, it will also
//redirect the input and output to the last valid file
int	open_red_loop(t_context *ctx, t_minishell *ms, int i) 
{
	int	j;

	j = 0;
	while (ctx->cmds[i]->reds[j] != NULL)
	{
		
	}
}