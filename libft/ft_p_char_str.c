/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_char_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:50:42 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:13 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char ch)
{
	ft_putchar_fd(ch, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	if (!str)
		return (ft_printstr("(null)"));
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}
