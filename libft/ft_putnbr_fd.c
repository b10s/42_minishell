/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:04:12 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:09 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_abs(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	int		i;
	char	numst[11];

	numst[10] = 0;
	if (n < 0)
		ft_putchar_fd('-', fd);
	num = ft_abs(n);
	i = 10;
	while (i > 0)
	{
		i--;
		numst[i] = (num % 10 + '0');
		num /= 10;
	}
	while (numst[i] == '0')
		i++;
	if (numst[i] == 0)
		i--;
	ft_putstr_fd(numst + i, fd);
}
