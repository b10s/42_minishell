/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_red_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:11:01 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/14 16:55:17 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_type(t_context *ctx, char *name, int type)

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