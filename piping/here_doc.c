/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:51:56 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/01 14:02:32 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ctrlderrormsg(int numlines, char *limiter, char *lines)
{
	free(lines);
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putnbr_fd(numlines, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("\')\n", 2);
}

char	*join_line_newline(char *lines, char *to_join)
{
	char	*newline;

	if (lines == NULL || to_join == NULL)
		exit(1);
	newline = ft_strjoin(lines, to_join);
	if (newline == NULL)
		exit(1);
	free(lines);
	free(to_join);
	return (newline);
}

int	write_lines(t_cmd *cmd, t_minishell *ms, char *lines, char *nline)
{
	free(nline);
	lines = ft_interpolate(lines, ms, 0);
	if (lines == NULL)
		exit(1);
	if (write(cmd->in_fd, lines, ft_strlen(lines)) == -1)
		exit(1);
	free(lines);
	return (EXIT_SUCCESS);
}

int	input_loop(t_cmd *cmd, t_minishell *ms, char *limiter, int numlines)
{
	char	*nline;
	char	*lines;
	int		limlen;

	limlen = ft_strlen(limiter);
	lines = (char *)ft_calloc(1, sizeof(char));
	if (lines == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		nline = readline("> ");
		if (g_signal == 2)
			return (free(lines), EXIT_FAILURE);
		if (nline == NULL && errno == 0)
			return (ctrlderrormsg(numlines, limiter, lines), EXIT_SUCCESS);
		if (errno != 0)
			return (free(lines), free(nline), EXIT_FAILURE);
		nline = join_line_newline(nline, ft_strdup("\n"));
		if (ft_strncmp(nline, limiter, limlen) == 0 && nline[limlen] == '\n')
			return (write_lines(cmd, ms, lines, nline));
		lines = join_line_newline(lines, nline);
		if (lines == NULL)
			return (EXIT_FAILURE);
		numlines++;
	}
}

int	put_input_in_here_doc(char *limiter, t_cmd *cmd, t_minishell *ms)
{
	int		numlines;

	errno = 0;
	numlines = 0;
	if (input_loop(cmd, ms, limiter, numlines) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(cmd->in_fd);
	cmd->in_fd = open(cmd->here_doc_filename, O_RDONLY);
	if (cmd->in_fd < 0)
		exit(1);
	return (EXIT_SUCCESS);
}
