/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_int_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:50:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:12 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(long num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

int	ft_printint(int num)
{
	ft_putnbr_fd(num, 1);
	if (num < 0)
		return (numlen(num) + 1);
	else
		return (numlen(num));
}

int	ft_printuint(unsigned int num)
{
	int		len;
	char	decrep[11];

	len = numlen(num);
	decrep[len] = 0;
	while (len)
	{
		len--;
		decrep[len] = (num % 10) + '0';
		num /= 10;
	}
	return (ft_printstr(decrep));
}
