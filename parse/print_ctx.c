/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/03/23 23:41:59 by aenshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

//TODO replace to ft_printf - double check if we can use printf
void	print_ctx(t_context *ctx)
{
	int	i;

	printf("\t=== print context ===\n");
	if (ctx->err != NULL)
	{
		printf("ctx has err: [%s]\n", ctx->err);
		return ;
	}
	i = 0;
	if (ctx->cmds == NULL)
		return ;
	while (ctx->cmds[i] != NULL)
	{
		print_cmd(ctx->cmds[i]);
		i++;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int	j;

	printf("\ncmd: ");
	if (cmd->cmd_with_args == NULL)
	{
		printf("cmd_with_args is NULL\n");
		return ;
	}
	j = 0;
	while (cmd->cmd_with_args[j] != NULL)
		printf(" [%s]", cmd->cmd_with_args[j++]);
	printf("\nred:\n");
	j = 0;
	while (cmd->reds[j] != NULL)
	{
		printf("  [%s] of type [%d]\n",
			cmd->reds[j]->fname_or_delim,
			cmd->reds[j]->type);
		j++;
	}
	printf("\n");
}
