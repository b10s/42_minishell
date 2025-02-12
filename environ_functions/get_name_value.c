/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:56:03 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/12 00:17:13 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

char	*get_name(char *namevalue)
{
	int	namelen;

	namelen = 0;
	while (namevalue[namelen] != '=')
		namelen++;
	return (ft_substr(namevalue, 0, namelen));
}

char	*get_value(char *namevalue)
{
	int		valuelen;

	valuelen = 0;
	while (*namevalue != '=')
		namevalue++;
	namevalue++;
	while (namevalue[valuelen] != '\0')
		valuelen++;
	return (ft_substr(namevalue, 0, valuelen));
}
