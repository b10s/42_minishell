/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/10 22:36:09 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "dirent.h"

//extern char **environ;

int	main(int argc, char *argv[], char *envp[])
{
	char		**args;
	t_variable	*vars;

	if (argc != 1)
		return (0);
	if (argv == NULL)
		return (0);
	if (envp == NULL)
		return (0);
	args = (char **)ft_calloc(2, sizeof(char *));
	args[0] = "VAR2=ok";
	vars = (t_variable *)ft_calloc(1, sizeof(t_variable));
	vars->content = "VAR=wow";
	export(args, vars);
	printf("%s\n", vars->next->content);
	free(vars->next);
	free(vars);
	free(args[0]);
	free(args);
	return (0);
}
