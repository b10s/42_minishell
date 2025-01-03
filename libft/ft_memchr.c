/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:03:25 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:14:17 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	size_t			i;

	s_ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_ptr[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc > 1)
// 	{
// 		char *h = argv[1];
// 		int n = argv[2][0];
// 		size_t	e = 4;
// 		if (ft_memchr(h, n, e) != memchr(h, n, e))
// 		{
// 			printf("NOOOOO");
// 		}
// 		printf("%s, %s", ft_memchr(h, n, e), memchr(h, n, e));
// 	}
// }