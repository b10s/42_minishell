/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:06:25 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/06 13:10:59 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_int(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0] == 0))
	{
		if (str[0] != '-' && str[0] != '+')
			return (0);
		i++;
	}
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i] == 0))
			return (0);
		i++;
	}
	return (1);
}

int	get_uchar(char *str)
{
	unsigned char	num;
	int				i;
	int				pos_or_neg;

	i = 0;
	pos_or_neg = 1;
	if (str[0] == '-')
		pos_or_neg = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	num = 0;
	while (str[i] != '\0')
	{
		num = (num * 10) + (pos_or_neg * (str[i] - '0'));
		i++;
	}
	return ((int)num);
}

//quits the shell, it exits with last signal by defualt otherwise
//it exits with the number given as argument, if the number is not a number
//it exits with 2 meaning error, 
int	cmd_exit(char **args, int last_status)
{
	int	arg;

	if (args[0] == NULL)
		exit(last_status);
	if (check_int(args[0]) == 0)
	{
		ft_putendl_fd(args[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	exit(get_char(args[0]));
}
