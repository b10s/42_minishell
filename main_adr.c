/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/12 00:19:53 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include "../libft/libft.h"

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

int	main(void)
{
	char	*str;
	char	*name;
	char	*value;

	str = "NAME=value";
	name = get_name(str);
	value = get_value(str);
	ft_printf("%s\n", name);
	ft_printf("%s\n", value);
	free(name);
	free(value);
}
