/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:23:27 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/01 14:10:42 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//prints current working directory
int	cmd_pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (buff != NULL)
	{
		ft_printf(buff);
		ft_printf("\n");
		free(buff);
		return (EXIT_SUCCESS);
	}
	else
		return (perror("getcwd: "), EXIT_FAILURE);
}
