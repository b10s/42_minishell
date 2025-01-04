/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:11:01 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:17:46 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(int c)
{
	if (64 < c && c < 91)
		return (1);
	return (0);
}

static int	ft_islower(int c)
{
	if (96 < c && c < 123)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (ft_isupper(c) || ft_islower(c))
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>

// int main()
// {
// 	int	a;
// 	a = -1;
// 	while (++a < 1000000)
// 	{
// 		if (ft_isalpha(a) != isalpha(a))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_isalpha(a), isalpha(a));
// 		}
// 	}
// 	char c;
// 	c = 0;
// 	while (1)
// 	{
// 		if (ft_isalpha(c) != isalpha(c))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_isalpha(c), isalpha(c));
// 		}
// 		c++;
// 		if (c == -1)
// 			break ;
// 	}
// }