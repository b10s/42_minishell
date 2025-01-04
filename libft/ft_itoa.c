/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:18:09 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:17:49 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_abs(int n)
{
	if (n < 0)
		return (-(long)n);
	return ((long)n);
}

static int	getnlen(int n)
{
	long	num;
	int		nlen;

	num = ft_abs(n);
	nlen = 0;
	while (num != 0)
	{
		num /= 10;
		nlen++;
	}
	if (n < 0)
		nlen++;
	if (n == 0)
		nlen++;
	return (nlen);
}

char	*ft_itoa(int n)
{
	long	num;
	char	*numst;
	int		nlen;

	nlen = getnlen(n);
	numst = (char *)malloc(nlen + 1);
	if (!numst)
		return (NULL);
	numst[nlen] = 0;
	num = ft_abs(n);
	while (nlen)
	{
		nlen--;
		numst[nlen] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		numst[0] = '-';
	return (numst);
}

// int main()
// {

// 	printf("%s\n", ft_itoa(-10));

// }