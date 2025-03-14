/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:11:33 by adrgutie          #+#    #+#             */
/*   Updated: 2025/03/14 21:57:32 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	get_logname(t_minishell *ms)
// {
// 	char	*logname;

// 	logname = ft_getenv("LOGNAME", ms->envs);
// 	if (logname == NULL)
// 	{
// 		logname = ft_getenv("USER", ms->envs);
// 		if (logname == NULL)
// 			logname = "unknown-user";
// 	}
// 	ms->logname = ft_strdup(logname);
// 	if (ms->logname == NULL)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

// int	get_hostname(t_minishell *ms)
// {
// 	int		hostnamefd;
// 	char	hostnamebuf[256];
// 	char	*newline;

// 	hostnamefd = open("/etc/hostname", O_RDONLY);
// 	if (hostnamefd == -1)
// 	{
// 		ms->hostname = ft_strdup("unknown-host");
// 		if (ms->hostname == NULL)
// 			return (EXIT_FAILURE);
// 		return (EXIT_SUCCESS);
// 	}
// 	ft_bzero(hostnamebuf, sizeof(hostnamebuf));
// 	if (read(hostnamefd, hostnamebuf, sizeof(hostnamebuf) - 1) == -1)
// 		return (close(hostnamefd), EXIT_FAILURE);
// 	close(hostnamefd);
// 	newline = ft_strchr(hostnamebuf, '\n');
// 	if (newline != NULL)
// 		*newline = '\0';
// 	ms->hostname = ft_strdup(hostnamebuf);
// 	if (ms->hostname == NULL)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

t_minishell	*init_minishell(void)
{
	t_minishell	*ms;

	ms = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
	if (ms == NULL)
		return (NULL);
	ms->line = NULL;
	ms->stdin_fd = -2;
	ms->stdout_fd = -2;
	ms->exit_status = 0;
	ms->envs = init_envs();
	if (ms->envs == NULL)
		return (free_minishell(ms), NULL);
	// if (get_logname(ms) == EXIT_FAILURE)
	// 	return (free_minishell(ms), NULL);
	// if (get_hostname(ms) == EXIT_FAILURE)
	// 	return (free_minishell(ms), NULL);
	return (ms);
}
