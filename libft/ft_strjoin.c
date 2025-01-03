/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:36:40 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:05 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = (char *)malloc(s1len + s2len + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, s1len + 1);
	ft_strlcpy(newstr + s1len, s2, s2len + 1);
	return (newstr);
}
