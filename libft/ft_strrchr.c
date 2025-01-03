/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:55:59 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:02 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	size_t	i;
	char	*last;

	last = 0;
	i = 0;
	ch = c;
	while (1)
	{
		if (s[i] == ch)
			last = (char *)(s + i);
		if (s[i] == 0)
			return (last);
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
// 		if (ft_strrchr(h, n) != strrchr(h, n))
// 		{
// 			printf("NOOOOO");
// 		}
// 		printf("%p, %p\n", ft_strrchr(h, n), strrchr(h, n));
// 	}
// }