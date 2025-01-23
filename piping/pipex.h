/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:28:56 by adrgutie          #+#    #+#             */
/*   Updated: 2025/01/23 19:45:23 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../parse/parse.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# define WRITE 1
# define READ 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define CLEAR_MEM -10

typedef struct s_pipex
{
	t_context	*ctx;
	int			in_fd;
	int			out_fd;
	char		*here_doc_filepath;
}	t_pipex;

//init
t_pipex	*init_spipex(t_context *ctx);

//free
void	free_spipex(t_pipex *spipex);

//here_doc
char	*find_unique_file_name(void);
char	*get_next_line(int fd);
#endif