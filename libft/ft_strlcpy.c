/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:47:23 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:04 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < dstsize)
		ft_memcpy(dst, src, srclen + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	return (srclen);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc > 3)
// 	{
// 		size_t	g = ft_atoi(argv[3]);
// 		char *dst = argv[1];
// 		char *dst2 = malloc(ft_strlen(dst) + 1);
// 		strcpy(dst2, dst);
// 		const char *src = argv[2];
// 		printf("return: %zu\n", strlcpy(dst, src, g));
// 		printf("strlcpy    new string: %s\n", dst);
// 		printf("return: %zu\n", ft_strlcpy(dst2, src, g));
// 		printf("ft_strlcpy new string: %s\n", dst2);
// 	}
// }