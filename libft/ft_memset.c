/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:16:41 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:14:17 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*b_ptr;

	b_ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		b_ptr[i] = c;
		i++;
	}
	return (b);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc > 3)
// 	{
// 		size_t	g = atoi(argv[3]);
// 		char *dst = argv[1];
// 		char *dst2 = malloc(strlen(dst) + 1);
// 		strcpy(dst2, dst);
// 		const char src = argv[2][0];
// 		printf("return: %s\n", memset(dst, src, g));
// 		printf("return: %s\n", ft_memset(dst2, src, g));
// 	}
// }