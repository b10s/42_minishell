/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:03:49 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:08 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_ar(char **ar, size_t i)
{
	while (i > 0)
	{
		i--;
		free(ar[i]);
	}
	free(ar);
	return (NULL);
}

static int	cw(char const *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	if (!s || !c)
		return (-1);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_strndup(const char *src, size_t n)
{
	char	*dupped;

	if (!src)
		return (NULL);
	dupped = (char *)malloc(n + 1);
	if (dupped == NULL)
		return (NULL);
	ft_memcpy(dupped, src, n);
	dupped[n] = 0;
	return (dupped);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	size_t		i;
	const char	*start;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (cw(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		start = s;
		while (*s != c && *s)
			s++;
		split[i] = ft_strndup(start, s - start);
		if (!split[i++])
			return (free_ar(split, i - 1), NULL);
	}
	split[i] = NULL;
	return (split);
}
