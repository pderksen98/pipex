/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 16:42:33 by pderksen      #+#    #+#                 */
/*   Updated: 2022/05/12 17:09:58 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
#include <unistd.h> //write
#include <limits.h> //OPEN_MAX
#include <sys/errno.h> //ernno
#include <fcntl.h> //open

typedef struct	s_pipex
{
	int f1;
	int f2;
	int fd;
	int cmd_count;
	int max_cmd;
}	t_pipex;

int		main(int argc, char **argv, char **envp);
char	*get_envp_path(char **envp);
#endif
