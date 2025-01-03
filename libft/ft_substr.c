/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:59:13 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:00 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start)
		len = 0;
	else if (len > slen)
		len = slen;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	if (start >= slen)
		start = slen;
	if (slen - start < len)
		len = slen - start;
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
