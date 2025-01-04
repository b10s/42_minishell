/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:24:27 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:02 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nl;
	size_t	sf;

	if (needle[0] == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	nl = 0;
	sf = 0;
	while (haystack[sf] && sf < len)
	{
		if (haystack[sf] == needle[nl])
		{
			while (haystack[sf + nl] == needle[nl] && (nl + sf) < len)
			{
				if (needle[nl + 1] == '\0')
					return ((char *)haystack + sf);
				nl++;
			}
			nl = 0;
		}
		sf++;
	}
	return (NULL);
}

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// {
// 	size_t	i;
// 	size_t	n;

// 	i = 0;
// 	n = 0;
// 	if (needle[0] == '\0')
// 		return ((char *)haystack);
// 	if (len == 0)
// 		return (0);
// 	while (haystack[i] != '\0' && i < len)
// 	{
// 		if (haystack[i] == needle[n])
// 		{
// 			while (haystack[i + n] == needle[n] && (i + n) < len)
// 			{
// 				if (needle[n + 1] == '\0')
// 					return ((char *)(haystack + i));
// 				n++;
// 			}
// 			n = 0;
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// int	main(int argc, char *argv[])
// {
// 	if (argc > 1)
// 	{
// 		char *h = argv[1];
// 		char *n = argv[2];
// 		int	e = atoi(argv[3]);
// 		if (ft_strnstr(h, n, e) != strnstr(h, n, e))
// 			printf("NOOOOO");
// 		printf("%s, %s\n", ft_strnstr(h, n, e), strnstr(h, n, e));
// 	}
// }

// int main(void)
// {
// 	char haystack[30] = "aaabcabcd";

// 	char needle[10] = "aabc";
// 	char *result = ft_strnstr(haystack, needle, -1);
// 	printf("result: %s\n", result);
// 	char *expected = strnstr(haystack, needle, -1);
// 	printf("expected: %s\n", expected);
// 	size_t i = -1;
// 	printf("overflow %lu \n", i);
// }