/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 18:20:48 by pderksen      #+#    #+#                 */
/*   Updated: 2022/05/12 17:17:08 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_envp_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	error(void)
{
	perror("Error");
	exit(errno);
}

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


char	*path_finder(char *cmd, char **paths)
{
	char	*path;
	char	*t_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		t_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(t_path, cmd);
		free(t_path);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	int		i;
	char	*env;
	char	**env_2d;
	char	**cmd;
	char	*path;

	env = get_envp_path(envp);
	env_2d = ft_split(env, ':');
	ft_check_malloc(env_2d);
	cmd = ft_split(argv, ' ');
	ft_check_malloc(cmd);
	path = path_finder(cmd[0], env_2d);
	if (!path)
	{
		i = -1;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0); //check this
		parent_process(argv, envp, fd);
	}
	else
		ft_putstr_fd("Not correct number of arguments\n", 2);
	return (0);
}
