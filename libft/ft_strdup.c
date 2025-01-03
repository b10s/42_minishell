/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:19:01 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:06 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	srcsize;
	char	*dupped;

	srcsize = ft_strlen(src) + 1;
	dupped = (char *)malloc(srcsize);
	if (dupped == NULL)
		return (NULL);
	ft_memcpy(dupped, src, srcsize);
	return (dupped);
}

// int main(void)
// {
// 	char *src = "Hello, World!";
// 	char *dup1 = ft_strdup(src);
// 	char *dup2 = strdup(src);

// 	printf("ft_strdup: %s\n", dup1);
// 	printf("strdup: %s\n", dup2);

// 	free(dup1);
// 	free(dup2);

// 	return 0;
// }