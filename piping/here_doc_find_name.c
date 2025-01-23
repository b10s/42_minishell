/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_find_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:10:47 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/23 17:13:04 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_itoa_noalloc(char *cnum, int number)
{
	int	nlen;
	int	i;

	i = number;
	nlen = 0;
	while (i != 0)
	{
		i /= 10;
		nlen++;
	}
	if (number < 0)
		i = 1;
	if (nlen == 0)
		nlen = 1;
	cnum[0] = '-';
	nlen = nlen + i;
	cnum[nlen] = '\0';
	while ((nlen - 1) >= i)
	{
		cnum[nlen - 1] = number % 10 + '0';
		if (number < 0)
			cnum[nlen - 1] = -(number % 10) + 10;
		number /= 10;
		nlen--;
	}
}

void	path_with_number(char *name, int number)
{
	char	cnum[30];

	ft_strlcat(name, "/tmp/here_doc", 30);
	ft_itoa_noalloc(cnum, number);
	ft_strlcat(name, cnum, 30);
}

char	*find_unique_file_name(void)
{
	int		numender;
	char	*name;

	name = (char *)ft_calloc(30, sizeof(char));
	if (name == NULL)
		return (NULL);
	ft_bzero(name, 30);
	numender = 0;
	while (numender < INT_MAX)
	{
		name[0] = 0;
		path_with_number(name, numender);
		if (access(name, F_OK) != 0)
			return (name);
		numender++;
	}
	return (free(name), NULL);
}
