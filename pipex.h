/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 16:42:33 by pderksen      #+#    #+#                 */
/*   Updated: 2022/06/23 11:31:31 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <unistd.h> //write
# include <limits.h> //OPEN_MAX
# include <sys/errno.h> //ernno
# include <fcntl.h> //open
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		f1;
	int		f2;
	int		last_cmd;
	int		current_cmd;
	char	**path_2d;
	char	**envp;
}	t_pipex;

int		main(int argc, char **argv, char **envp);
void	pipex(t_pipex p, char **argv);
void	error_message(char *message);
void	error(void);
void	parent_process(int *fd, pid_t child);
void	parent_process_2(pid_t child);
void	child_process(int *fd, char **argv, t_pipex *p);
void	child_process_2(char **argv, t_pipex *p);
void	execute(char *cmd, char **path_2d, char **envp);
char	*path_finder(char *cmd, char **path_2d);
void	exit_wrong_command(char **cmd);
char	*find_paths(char **env);
#endif
