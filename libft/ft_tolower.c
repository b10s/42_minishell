/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:21:52 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:00 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (64 < c && c < 91)
		c += 32;
	return (c);
}

// int main()
// {
// 	int	a;
// 	a = -1;
// 	while (++a < 350)
// 	{
// 		if (ft_tolower(a) != tolower(a))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_tolower(a), tolower(a));
// 		}
// 	}

// }
