/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:39:35 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:10 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dealwithit(const char ch, va_list args)
{
	if (ch == 'c')
		return (ft_printchar(va_arg(args, int)));
	else if (ch == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (ch == 'p')
		return (ft_printptr(va_arg(args, void *)));
	else if (ch == 'd' || ch == 'i')
		return (ft_printint(va_arg(args, int)));
	else if (ch == 'u')
		return (ft_printuint(va_arg(args, unsigned int)));
	else if (ch == 'x')
		return (ft_printuhex(va_arg(args, unsigned int), 0));
	else if (ch == 'X')
		return (ft_printuhex(va_arg(args, unsigned int), 1));
	else if (ch == '%')
		return (ft_printchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str != '%')
			count += ft_printchar(*str);
		else
		{
			str++;
			count += dealwithit(*str, args);
		}
		str++;
	}
	va_end(args);
	return (count);
}
