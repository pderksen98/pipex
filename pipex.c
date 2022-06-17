/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 18:20:48 by pderksen      #+#    #+#                 */
/*   Updated: 2022/06/17 11:59:06 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	exit(errno);
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	f1;

	close(fd[0]);
	f1 = open(argv[1], O_RDONLY);
	if (f1 == -1)
		error_message(argv[1]);
	dup2(f1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	f2;

	close(fd[1]);
	f2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (f2 == -1)
		error();
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
