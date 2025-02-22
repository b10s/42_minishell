/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:51:56 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/23 01:02:45 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ctrlderrormsg(int numlines, char *limiter, char *line)
{
	char	*numlinesstr;

	get_next_line(CLEAR_MEM);
	free(line);
	numlinesstr = ft_itoa(numlines);
	if (numlinesstr == NULL)
		return (EXIT_FAILURE);
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(numlinesstr, 2);
	free(numlinesstr);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("\')\n", 2);
	return (EXIT_SUCCESS);
}

int	input_loop(t_pipex *spipex, char *limiter, int limlen, int numlines)
{
	char	*line;

	while (1)
	{
		printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (EXIT_FAILURE);
		if (line[0] == '\0')
			return (ctrlderrormsg(numlines, limiter, line));
		if (ft_strncmp(line, limiter, limlen) == 0 && line[limlen] == '\n')
			return (get_next_line(CLEAR_MEM), free(line), EXIT_SUCCESS);
		if (write(spipex->in_fd, line, ft_strlen(line)) == -1)
		{
			return (free(line), get_next_line(CLEAR_MEM), \
			perror("write"), EXIT_FAILURE);
		}
		free(line);
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
