/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:55:59 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:07 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	size_t	i;

	i = 0;
	ch = c;
	while (1)
	{
		if (s[i] == ch)
			return ((char *)(s + i));
		if (s[i] == 0)
			return (NULL);
		i++;
	}
}

// #include <stdio.h>
// #include <string.h>

// int	main(int argc, char *argv[])
// {
// 	if (argc > 1)
// 	{
// 		char *h = argv[1];
// 		int n = argv[2][0];
// 		if (ft_strchr(h, n) != strchr(h, n))
// 		{
// 			printf("NOOOOO");
// 		}
// 		printf("%p, %p\n", ft_strchr(h, n), strchr(h, n));
// 	}
// }