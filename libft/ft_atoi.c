/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:12:45 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/03 16:17:43 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	whitepass(const char *str)
{
	size_t	i;
	char	c;

	i = 0;
	c = str[i];
	while ((c > 8 && c < 14) || c == 32)
	{
		i++;
		c = str[i];
	}
	return (i);
}

static char	isneg(const char *str, size_t *i)
{
	char	neg;

	neg = 0;
	if (str[*i] == '-')
	{
		neg = 1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	return (neg);
}

static unsigned long	addup(const char *str, size_t i, char neg)
{
	unsigned long	an;
	unsigned long	check;

	check = LONG_MAX / 10;
	an = 0;
	while (ft_isdigit(str[i]))
	{
		if (an > check || (an * 10 + (str[i] - '0')) > LONG_MAX)
		{
			if (neg)
			{
				an = LONG_MAX;
				an++;
			}
			else
				an = LONG_MAX;
			break ;
		}
		else
			an = an * 10 + (str[i] - '0');
		i++;
	}
	return (an);
}

int	ft_atoi(const char *str)
{
	size_t			i;
	unsigned long	an;
	long			answer;
	char			neg;

	i = whitepass(str);
	neg = isneg(str, &i);
	an = addup(str, i, neg);
	if (neg)
		answer = ~an + 1;
	else
		answer = an;
	return ((int)answer);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc == 2)
// 	{
// 		printf("%d\n", (int)strtol(argv[1], (char **) NULL, 10));
// 		printf("%d\n", ft_atoi(argv[1]));
// 	}
// }