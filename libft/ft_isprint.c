/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:23:35 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:17:48 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (31 < c && c < 127)
		return (1);
	return (0);
}

// int main()
// {
// 	int	a;

// 	a = -1;
// 	while (++a < 350)
// 	{
// 		if (ft_isprint(a) != isprint(a))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_isprint(a), isprint(a));
// 		}
// 	}
// 	char x = 0;
// 	unsigned char c;
// 	c = 0;
// 	while (x < 2)
// 	{
// 		if (c == 0)
// 			x++;
// 		if (ft_isprint(c) != isprint(c))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_isprint(c), isprint(c));
// 		}
// 		c++;
// 	}
// }
