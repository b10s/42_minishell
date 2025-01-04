/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:44:45 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:17:44 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// int	main(int argc, char *argv[])
// {
// 	char test[20] = "123456789012";
// 	char test2[20] = "12345789012";
// 	bzero(test, 7);
// 	ft_bzero(test2, 7);
// 	int t;
// 	int t2;
// 	int i;

// 	t = 0;
// 	t2 = 0;
// 	i = 0;
// 	while (i < 10)
// 	{
// 		if (test[i] == 0)
// 			t++;
// 		if (test2[i] == 0)
// 			t2++;
// 		i++;

// 	}
// 	printf("%d, %d\n", t, t2);
// }