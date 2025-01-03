/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:12:33 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:17:45 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>

// int main()
// {
// 	int	a;
// 	a = -1;
// 	while (++a < 350)
// 	{
// 		if (ft_isalnum(a) != isalnum(a))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_isalnum(a), isalnum(a));
// 		}
// 	}
// 	char c;
// 	c = 0;
// 	while (1)
// 	{
// 		if (ft_isalnum(c) != isalnum(c))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_isalnum(c), isalnum(c));
// 		}
// 		c++;
// 		if (c == -1)
// 			break ;
// 	}
// }