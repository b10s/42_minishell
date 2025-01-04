/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:03:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:17:46 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (-1 < c && c < 128)
		return (1);
	return (0);
}

// int main()
// {
// 	int	a;
// 	a = -1;
// 	while (++a < 1000000)
// 	{
// 		if (ft_isascii(a) != isascii(a))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_isascii(a), isascii(a));
// 		}
// 	}
// 	char c;
// 	c = 0;
// 	while (1)
// 	{
// 		if (ft_isascii(c) != isascii(c))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_isascii(c), isascii(c));
// 		}
// 		c++;
// 		if (c == 255)
// 			break ;
// 	}
// }
