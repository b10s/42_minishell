/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:17:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:01 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	leftpass(char const *s1, char const *set)
{
	size_t	setlen;
	size_t	i;

	setlen = ft_strlen(set);
	i = 0;
	while (ft_memchr(set, s1[i], setlen))
		i++;
	return (i);
}

static size_t	rightpass(char const *s1, char const *set)
{
	size_t	setlen;
	size_t	i;

	setlen = ft_strlen(set);
	i = ft_strlen(s1);
	while (i > 0)
	{
		i--;
		if (!ft_memchr(set, s1[i], setlen))
			break ;
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimd;

	if (!s1 || !set)
		return (NULL);
	start = leftpass(s1, set);
	if (start == ft_strlen(s1))
		end = start;
	else
		end = rightpass(s1, set);
	trimd = (char *)malloc(end - start + 1);
	if (!trimd)
		return (NULL);
	ft_strlcpy(trimd, s1 + start, end - start + 1);
	return (trimd);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc > 1)
// 	{
// 		printf("%s\n", ft_strtrim(argv[1], argv[2]));
// 	}
// }