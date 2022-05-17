/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 18:20:48 by pderksen      #+#    #+#                 */
/*   Updated: 2022/05/17 13:40:31 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	f1;

	f1 = open(argv[1], O_RDONLY);
	if (f1 == -1)
		error();
	close(fd[0]);
	dup2(f1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	f2;

	f2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (f2 == -1)
		error();
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	int		status;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, &status, 0);
		parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("Not correct number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	return (0);
}
