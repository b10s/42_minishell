/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:11:35 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:14:17 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d_ptr;
	unsigned char	*s_ptr;

	d_ptr = (unsigned char *)dest;
	s_ptr = (unsigned char *)src;
	if (s_ptr < d_ptr)
	{
		while (n > 0)
		{
			n--;
			d_ptr[n] = s_ptr[n];
		}
	}
	else
		ft_memcpy(d_ptr, s_ptr, n);
	return (dest);
}
