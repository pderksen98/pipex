/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 16:42:33 by pderksen      #+#    #+#                 */
/*   Updated: 2022/06/17 12:00:25 by pderksen      ########   odam.nl         */
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

int		main(int argc, char **argv, char **envp);
void	execute(char *argv, char **envp);
char	*path_finder(char *cmd, char **paths);
void	parent_process(char **argv, char **envp, int *fd);
void	child_process(char **argv, char **envp, int *fd);
void	error(void);
void    error_message(char *message);
char	*get_envp_path(char **envp);
void	exit_wrong_command(char **cmd);
#endif
