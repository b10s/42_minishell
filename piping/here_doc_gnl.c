/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:39:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/23 19:45:04 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen_special(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

void	shift_buf_left(char buf[], int buflen)
{
	int	i;

	i = 0;
	while (buf[buflen + i] != '\0')
	{
		buf[i] = buf[i + buflen];
		i++;
	}
	buf[i] = '\0';
}

char	*join_buf_line(char *line, char buf[])
{
	int		linelen;
	int		buflen;
	char	*newline;
	int		i;

	if (line == NULL)
	{
		line = (char *)malloc(1);
		if (line == NULL)
			return (NULL);
		line[0] = 0;
	}
	linelen = ft_strlen_special(line);
	buflen = ft_strlen_special(buf);
	newline = (char *)malloc(linelen + buflen + 1);
	if (newline == NULL)
		return (free(line), NULL);
	i = -1;
	while (++i < linelen)
		newline[i] = line[i];
	i = -1;
	while (++i < buflen)
		newline[linelen + i] = buf[i];
	newline[linelen + buflen] = '\0';
	return (free(line), shift_buf_left(buf, buflen), newline);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			br;

	if (fd == CLEAR_MEM)
		return (ft_bzero(buf, sizeof(buf)), NULL);
	line = NULL;
	br = 0;
	while (1)
	{
		if (buf[0] == 0)
		{
			br = read(fd, buf, BUFFER_SIZE);
			if (br < 0)
				return (free(line), buf[0] = 0, NULL);
			if (br == 0)
				return (line);
			buf[br] = 0;
		}
		line = join_buf_line(line, buf);
		if (line == NULL)
			return (buf[0] = 0, NULL);
		if (line[ft_strlen_special(line) - 1] == '\n')
			return (line);
	}
}
