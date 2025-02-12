/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:56:03 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/12 23:06:35 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ_functions.h"

char	*get_name(char *namevalue)
{
	int		namelen;
	char	*name;

	namelen = 0;
	while (namevalue[namelen] != '=')
		namelen++;
	name = ft_substr(namevalue, 0, namelen);
	return (name);
}

char	*get_value(char *namevalue)
{
	int		valuelen;
	char	*value;

	valuelen = 0;
	while (*namevalue != '=')
		namevalue++;
	namevalue++;
	while (namevalue[valuelen] != '\0')
		valuelen++;
	value = ft_substr(namevalue, 0, valuelen);
	return (value);
}
