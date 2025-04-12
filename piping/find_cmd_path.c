/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:56:22 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/11 22:50:25 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_exit_paths(char **paths, char **cmd_path, int exit_value, int prrr)
{
	if (prrr == 1)
	{
		if (ft_strchr(*cmd_path, '/') == NULL)
			exit_value = 127;
		if (exit_value == 127)
		{
			ft_putstr_fd(*cmd_path, 2);
			ft_putstr_fd(": command not found: \n", 2);
		}
		if (exit_value == 126)
		{
			ft_putstr_fd(*cmd_path, 2);
			ft_putstr_fd(": permission denied: \n", 2);
		}
	}
	free_split(paths);
	if (*cmd_path != NULL)
		free(*cmd_path);
	exit(exit_value);
}

char	**get_paths(char **env_cpy)
{
	char	**paths;
	int		i;

	i = 0;
	while (env_cpy[i] != NULL)
	{
		if (ft_strncmp(env_cpy[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env_cpy[i] + 5, ':');
			if (paths == NULL)
				exit(1);
			return (paths);
		}
		i++;
	}
	paths = (char **)ft_calloc(2, sizeof(char *));
	if (paths == NULL)
		exit(1);
	paths[0] = (char *)ft_calloc(1, sizeof(char *));
	if (paths[0] == NULL)
		exit(1);
	return (paths);
}

char	*join_path_cmd(char *path, char *cmd)
{
	char	*path_fslash;
	char	*joined;

	path_fslash = ft_strjoin(path, "/");
	if (path_fslash == NULL)
		exit(1);
	joined = ft_strjoin(path_fslash, cmd);
	free(path_fslash);
	return (joined);
}

char	*r_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*joined_path;

	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i] != NULL)
	{
		joined_path = join_path_cmd(paths[i], cmd);
		if (joined_path == NULL)
			exit(1);
		if (access(joined_path, F_OK) == 0)
			return (joined_path);
		free(joined_path);
		i++;
	}
	return (ft_strdup(cmd));
}

char	*find_cmd_path(char *cmd, t_envs *envs)
{
	char	**paths;
	char	*cmd_path;

	if (cmd[0] == '\0')
	{
		ft_putstr_fd(": command not found: \'\'\n", 2);
		exit(127);
	}
	cmd_path = NULL;
	paths = get_paths(envs->env_cpy);
	if (paths == NULL)
		exit(1);
	cmd_path = r_cmd_path(paths, cmd);
	if (cmd_path == NULL)
		exit(1);
	if (ft_strchr(cmd_path, '/') == NULL)
		free_exit_paths(paths, &cmd_path, 127, 1);
	if (access(cmd_path, F_OK) != 0)
		free_exit_paths(paths, &cmd_path, 127, 1);
	if (access(cmd_path, X_OK) != 0)
		free_exit_paths(paths, &cmd_path, 126, 1);
	free_split(paths);
	return (cmd_path);
}
