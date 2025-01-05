/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:31:48 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/05 23:11:19 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "dirent.h"

//extern char **environ;

int	main(int argc, char *argv[], char *envp[])
{
	DIR				*dir;
	struct dirent	*entry;
	char			**args;

	if (argc != 1)
		return (0);
	if (argv == NULL)
		return (0);
	if (envp == NULL)
		return (0);
	cd("libft");
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (1);
	}
	args = calloc(2, sizeof(char *));
	if (args == NULL)
		return (1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		args[0] = entry->d_name;
		args[1] = NULL;
		echo(1, args);
		entry = readdir(dir);
	}
	closedir(dir);
	free(args);
	return (0);
}
