/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/16 20:11:25 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/minishell.h"
#include "libft/libft.h"
#include "readline/readline.h"
#include "environ_functions/environ_functions.h"
#include "builtins/builtins.h"
#include "parse/parse.h"

int	main(void)
{
	char	*line;
	t_envs	*envs;

	envs = init_envs();
	line = ft_strdup("123$THIS456$this_should_not_be_here$123123");
	line = ft_interpolate(line, envs, NULL);
	ft_printf("%s\n", line);
	free(envs);
	free(line);
}
