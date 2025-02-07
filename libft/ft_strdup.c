/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:19:01 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/06 15:41:05 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	srcsize;
	char	*dupped;
	size_t	i;

	srcsize = ft_strlen(src) + 1;
	dupped = (char *)malloc(srcsize);
	if (dupped == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dupped[i] = src[i];
		i++;
	}
	dupped[i] = '\0';
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