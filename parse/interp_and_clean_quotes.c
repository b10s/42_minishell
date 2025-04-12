/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interp_and_clean_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:13:44 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/12 18:23:14 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	cleanup_commands_inner_loop(t_cmd *cmd, t_minishell *ms)
{
	int	j;

	j = 0;
	while (cmd->cmd_with_args[j] != NULL)
	{
		cmd->cmd_with_args[j] = ft_interpolate(cmd->cmd_with_args[j], ms, 1);
		cmd->cmd_with_args[j] = remove_a_layer_of_quotes(cmd->cmd_with_args[j]);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	cleanup_reds_inner_loop(t_red **reds, t_minishell *ms)
{
	int	k;

	k = 0;
	while (reds[k] != NULL)
	{
		reds[k]->fname_or_delim = \
		ft_interpolate(reds[k]->fname_or_delim, ms, 1);
		reds[k]->fname_or_delim = \
		remove_a_layer_of_quotes(reds[k]->fname_or_delim);
		k++;
	}
	return (EXIT_SUCCESS);
}

int	interp_remquotelayer(t_context *ctx, t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < ctx->cmd_cnt)
	{
		cleanup_commands_inner_loop(ctx->cmds[i], ms);
		cleanup_reds_inner_loop(ctx->cmds[i]->reds, ms);
		i++;
	}
	return (EXIT_SUCCESS);
}
