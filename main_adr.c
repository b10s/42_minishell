/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/09 01:13:41 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

int	white_sign_skip(char *str, int *sign)
{
	int	i;

	*sign = 1;
	i = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		*sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

int	num_loop(char *str, int i, int sign)
{
	long	num;
	int		digit;

	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (sign == 1 && (num > (LONG_MAX - digit) / 10))
			return (0);
		if (sign == -1 && (num > (-(LONG_MIN + digit)) / 10))
			return (0);
		num = (num * 10) + digit;
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	is_numeric(char *str)
{
	int		sign;
	int		i;

	sign = 1;
	i = white_sign_skip(str, &sign);
	if (str[i] < '0' || str[i] > '9')
		return (0);
	return (num_loop(str, i, sign));
}

int	main(void)
{
	char	*str;

	str = "100000000000";
	printf("%d\n", is_numeric(str));
}
