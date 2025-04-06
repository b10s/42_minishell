/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:48:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/06 20:51:57 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define I 0
#define DQ 1
#define SQ 2
#define TYPE 3
#define IN_OUT 1
#define HD_AM 2
#define PIPE 3

int	is_special(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	find_type(char *line)
{
	if (line[0] == '|')
		return (PIPE);
	if (line[0] == '>')
	{
		if (line[1] == '>')
			return (HD_AM);
		return (IN_OUT);
	}
	if (line[0] == '<')
	{
		if (line[1] == '<')
			return (HD_AM);
		return (IN_OUT);
	}
	return (0);
}

int	check_after(char *line, int a[4])
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (EXIT_FAILURE);
	if (a[TYPE] == PIPE && *line == '|')
		return (EXIT_FAILURE);
	if (a[TYPE] == HD_AM || a[TYPE] == IN_OUT)
	{
		if (*line == '<' || *line == '>' || *line == '|')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	syntax_check(char *line)
{
	int	a[4];

	if (*line == '|')
		return (2);
	ft_bzero(a, sizeof(a));
	while (line[a[I]] != '\0')
	{
		if (line[a[I]] == '\'' && a[DQ] == 0)
			a[SQ] = a[SQ] ^ 1;
		else if (line[a[I]] == '\"' && a[SQ] == 0)
			a[DQ] = a[DQ] ^ 1;
		if (is_special(line[a[I]]) == 1 && a[DQ] == 0 && a[SQ] == 0)
		{
			a[TYPE] = find_type(line + a[I]);
			if (a[TYPE] == HD_AM)
				a[I] += 2;
			else
				a[I]++;
			if (check_after(line + a[I], a) == EXIT_FAILURE)
				return (2);
			continue ;
		}
		a[I]++;
	}
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc < 2)
// 		return (1);
// 	if (syntax_check(argv[1]) == 2)
// 		printf("syntax error!!!!\n");
// 	else
// 		printf("no error\n");
// 	return (0);
// }
