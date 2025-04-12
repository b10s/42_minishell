/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:00:22 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/12 21:58:53 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_cmd_error(char *cmd, char *error_msg)
{
	char	*combo;

	combo = ft_strjoin(cmd, error_msg);
	if (combo == NULL)
		exit(1);
	ft_putstr_fd(combo, 2);
	free(combo);
}
