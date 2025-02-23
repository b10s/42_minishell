/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:51:56 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/24 00:25:17 by adrgutie         ###   ########.fr       */
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
	int		fail;

	newline = ft_strjoin(lines, to_join);
	free(lines);
	free(to_join);
	return (newline);
}

int	write_lines(t_pipex *spipex, char *lines, char *nline)
{
	if (write(spipex->in_fd, lines, ft_strlen(lines)) == -1)
	{
		free(nline);
		free(lines);
		perror("write");
		return (EXIT_FAILURE);
	}
	lines = join_line_newline(lines, nline);
	if (lines == NULL)
		return (EXIT_FAILURE);
	add_history(lines);
	free(lines);
	return (EXIT_SUCCESS);
}

int	input_loop(t_pipex *spipex, char *limiter, int limlen, int numlines)
{
	char	*nline;
	char	*lines;

	lines = (char *)ft_calloc(1, sizeof(char));
	if (lines == NULL)
		return (EXIT_FAILURE);
	errno = 0;
	while (1)
	{
		nline = readline(">");
		if (nline == NULL && errno == 0)
			return (ctrlderrormsg(numlines, limiter, lines), EXIT_SUCCESS);
		if (errno != 0)
			return (free(lines), free(nline), EXIT_FAILURE);
		if (ft_strncmp(nline, limiter, limlen) == 0 && nline[limlen] == '\n')
			return (write_lines(spipex, lines, nline));
		lines = join_line_newline(lines, nline);
		if (lines == NULL)
			return (EXIT_FAILURE);
		numlines++;
	}
}

int	put_input_in_here_doc(t_pipex *spipex)
{
	char	*limiter;
	int		limlen;
	int		numlines;

	limiter = spipex->ctx->here_doc_delim;
	numlines = 0;
	limlen = ft_strlen(limiter);
	if (input_loop(spipex, limiter, limlen, numlines) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(spipex->in_fd);
	spipex->in_fd = open(spipex->here_doc_filepath, O_RDONLY);
	if (spipex->in_fd < 0)
		return (perror("open"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
