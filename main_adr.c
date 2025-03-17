/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/17 21:42:43 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/minishell.h"
#include "libft/libft.h"
#include "readline/readline.h"
#include "environ_functions/environ_functions.h"
#include "ms/minishell.h"
#include "builtins/builtins.h"
#include "parse/parse.h"

int	main(void)
{
	char		*line;
	t_minishell	*ms;

	ms = init_minishell();
	line = ft_strdup("$?$USER $HOME");
	line = ft_interpolate(line, ms);
	ft_printf("%s\n", line);
	free_minishell(ms);
	free(line);
}
