/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:04:32 by adrgutie          #+#    #+#             */
/*   Updated: 2025/02/13 22:01:52 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_FUNCTIONS_H
# define ENVIRON_FUNCTIONS_H

# include "../libft/libft.h"



//this global variable automatically holds the environment variables
extern char				**environ;

//structure to hold the copy of the environ variable
typedef struct s_envs
{
	char		**env_cpy;
}	t_envs;

//free
void	free_envs(t_envs *envs);
void	free_split(char **split);

//init
t_envs	*init_envs(void);

//env functions
char	*ft_getenv(const char *name, t_envs *envs);
int		ft_setenv(const char *name, const char *value, \
						int overwrite, t_envs *envs);
int		ft_unsetenv(const char *name, t_envs *envs);
//get
char	*get_name(char *namevalue);
char	*get_value(char *namevalue);
int		get_variable_pos(const char *name, t_envs *envs);

#endif