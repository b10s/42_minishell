/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:45:44 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:04 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// #include <stdio.h>
// #include <string.h>

// int	main(int argc, char *argv[])
// {
// 	int i = 0;
// 	while (++i < argc)
// 	{
// 		char *t = argv[i];
// 		if (ft_strlen(argv[i]) != strlen(argv[i]))
// 		{
// 			printf("Huh?, this is where it went wrong %s\n", t);
// 			printf("%lu, %lu\n", ft_strlen(t), strlen(t));
// 		}
// 	}
// }
