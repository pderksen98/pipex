/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 09:58:30 by pderksen      #+#    #+#                 */
/*   Updated: 2022/06/17 12:49:43 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//F_OK checks whether the file exists
//R_OK checks whether the file exists and grants Read permissions
//W_OK checks whether the file exists and grants Write permissions
//X_OK checks whether the file exists and grants Execute permissions
//On succes 0 is returned, else -1

void	error(void)
{
	perror("Error");
	exit(errno);
}

char	*get_envp_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*path_finder(char *cmd, char **paths)
{
	char	*path;
	char	*temp_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		ft_check_malloc(temp_path);
		path = ft_strjoin(temp_path, cmd);
		ft_check_malloc(path);
		free(temp_path);
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

void	exit_wrong_command(char **cmd)
{
	if (ft_strchr(cmd[0], '/'))
		error();
	else
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

void	execute(char *argv, char **envp)
{
	char	*env;
	char	**env_2d;
	char	**cmd;
	char	*path;

	env = get_envp_path(envp);
	env_2d = ft_split(env, ':');
	ft_check_malloc(env_2d);
	cmd = ft_split(argv, ' ');
	ft_check_malloc(cmd);
	if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == 0)
	{
		path = cmd[0];
		if (execve(path, cmd, envp) == -1)
			error();
	}
	path = path_finder(cmd[0], env_2d);
	if (!path)
		exit_wrong_command(cmd);
	if (execve(path, cmd, envp) == -1)
		error();
}
