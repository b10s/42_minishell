/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/18 23:26:02 by adrgutie         ###   ########.fr       */
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
	errno = 0;
	free(NULL);
	free(NULL);
	printf("%d\n", errno);
}
