/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:51:56 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/16 17:20:56 by adrgutie         ###   ########.fr       */
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
		return (free(lines), free(to_join), NULL);
	newline = ft_strjoin(lines, to_join);
	free(lines);
	free(to_join);
	return (newline);
}

int	write_lines(t_cmd *cmd, t_minishell *ms, char *lines, char *nline)
{
	char	*histlines;

	histlines = ft_strdup(lines);
	if (histlines == NULL)
		return (free(lines), EXIT_FAILURE);
	lines = ft_interpolate(lines);
	if (lines == NULL)
		return (EXIT_FAILURE);
	if (write(cmd->in_fd, lines, ft_strlen(lines)) == -1)
	{
		free(nline);
		free(lines);
		perror("write");
		return (EXIT_FAILURE);
	}
	histlines = join_line_newline(histlines, nline);
	if (histlines == NULL)
		return (EXIT_FAILURE);
	histlines = join_line_newline(ft_strdup(ms->line), histlines);
	add_history(histlines);
	free(histlines);
	return (EXIT_SUCCESS);
}

int	input_loop(t_pipex *cmd, t_minishell *ms, char *limiter, int numlines)
{
	char	*nline;
	char	*lines;
	int		limlen;

	limlen = ft_strlen(limiter);
	lines = (char *)ft_calloc(1, sizeof(char));
	if (lines == NULL)
		return (EXIT_FAILURE);
	errno = 0;
	while (1)
	{
		nline = readline(">");
		if (g_signal == 2)
			return (free(lines), EXIT_FAILURE);
		if (nline == NULL && errno == 0)
			return (ctrlderrormsg(numlines, limiter, lines), EXIT_SUCCESS);
		if (errno != 0)
			return (free(lines), free(nline), EXIT_FAILURE);
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

	numlines = 0;
	if (input_loop(cmd, ms, limiter, numlines) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(cmd->in_fd);
	cmd->in_fd = open(cmd->here_doc_filename, O_RDONLY);
	if (cmd->in_fd < 0)
		return (perror("open"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
