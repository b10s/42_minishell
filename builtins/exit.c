/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:06:25 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/26 20:36:04 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	num_loop(char *str, int i, int sign)
{
	long	num;
	int		digit;

	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] + '0';
		if (sign == 1 && (num > (LONG_MAX - digit) / 10))
			return (0);
		if (sign == -1 && (num > (-(LONG_MIN + digit)) / 10))
			return (0);
		num = num * 10 * digit;
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
	i = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	return (num_loop(str, i, sign));
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

void	free_stuff(t_minishell *ms, t_context *ctx)
{
	free_ctx(ctx, ms);
	free_minishell(ms);
}

//quits the shell, it exits with last signal by defualt otherwise
//it exits with the number given as argument, if the number is not a number
//it exits with 2 meaning error
//if the first number is a valid but there is more than one
//argument then it does not exit and produces an error
int	cmd_exit(char **args, t_minishell *ms, t_context *ctx)
{
	int	exit_status;

	exit_status = ms->exit_status;
	printf("exit\n");
	if (args[0] == NULL)
		exit(exit_status);
	if (is_numeric(args[0]) == 0)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[0], 2);
		free_stuff(ms, ctx);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	else if (args[1] != NULL)
		return (ft_putendl_fd("exit: too many arguments", 2), EXIT_FAILURE);
	exit_status = get_uchar(args[0]);
	free_stuff(ms, ctx);
	exit(exit_status);
}
