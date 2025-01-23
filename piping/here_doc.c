/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:51:56 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/23 19:45:16 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ctrlderrormsg(int numlines, char *limiter, char *line)
{
	char	*numlinesstr;

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

int	put_input_in_here_doc(t_pipex *spipex)
{
	int		numlines;
	char	*line;
	int		limlen;
	char	*limiter;

	numlines = 1;
	limiter = spipex->ctx->here_doc_delim;
	limlen = ft_strlen(limiter);
	while (1)
	{
		printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (EXIT_FAILURE);
		if (line[0] == '\0')
			return (ctrlderrormsg(numlines, limiter, line));
		if (ft_strncmp(line, limiter, limlen) == 0 && line[limlen] == '\n')
			break ;
		write(spipex->in_fd, line, ft_strlen(line));
	}
}
