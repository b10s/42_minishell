/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:57:55 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/08 03:39:38 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_error(void)
{
	perror("open");
	if (errno == ENFILE || errno == EMFILE || errno == EIO)
        exit(1);
	return (EXIT_FAILURE);
}

int	open_in(char *name, t_cmd *cmd)
{
	if (cmd->here_doc_filename != NULL)
	{
		unlink(cmd->here_doc_filename);
		free(cmd->here_doc_filename);
		cmd->here_doc_filename = NULL;
	}
	close_set_gen(&(cmd->in_fd));
	cmd->in_fd = open(name, O_RDONLY);
	if (cmd->in_fd == -1)
		return (open_error());
	return (EXIT_SUCCESS);
}

int	open_out(char *name, t_cmd *cmd)
{
	close_set_gen(&(cmd->out_fd));
	cmd->out_fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->out_fd == -1)
		return (open_error());
	return (EXIT_SUCCESS);
}

int	open_out_append(char *name, t_cmd *cmd)
{
	close_set_gen(&(cmd->out_fd));
	cmd->out_fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->out_fd == -1)
		return (open_error());
	return (EXIT_SUCCESS);
}

int	open_here_doc(char *limiter, t_cmd *cmd, t_minishell *ms)
{
	if (cmd->here_doc_filename != NULL)
	{
		unlink(cmd->here_doc_filename);
		free(cmd->here_doc_filename);
		cmd->here_doc_filename = NULL;
	}
	close_set_gen(&(cmd->in_fd));
	cmd->here_doc_filename = find_unique_file_name();
	if (cmd->here_doc_filename == NULL)
		exit(1);
	cmd->in_fd = open(cmd->here_doc_filename, O_WRONLY | O_CREAT, 0644);
	if (cmd->in_fd == -1)
		return (open_error());
	if (put_input_in_here_doc(limiter, cmd, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
