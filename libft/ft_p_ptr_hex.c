/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_ptr_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:50:53 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:12 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	findplen(uintptr_t pint)
{
	int	plen;

	if (pint == 0)
		return (1);
	plen = 0;
	while (pint)
	{
		pint /= 16;
		plen++;
	}
	return (plen);
}

static char	hextochar(int num, int upper)
{
	char	a;

	a = 'a';
	if (upper)
		a = 'A';
	if (num < 10)
		return ('0' + num);
	else
		return (a + (num - 10));
}

int	ft_printuhex(uintptr_t num, int upper)
{
	int			len;
	char		hexform[17];
	int			hexdigit;

	len = findplen(num);
	hexform[len] = 0;
	while (len)
	{
		len--;
		hexdigit = num & 0xF;
		hexform[len] = hextochar(hexdigit, upper);
		num >>= 4;
	}
	return (ft_printstr(hexform));
}

int	ft_printptr(void *ptr)
{
	ft_putstr_fd("0x", 1);
	return (ft_printuhex((uintptr_t)ptr, 0) + 2);
}
