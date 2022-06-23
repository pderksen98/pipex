/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 11:25:09 by pderksen      #+#    #+#                 */
/*   Updated: 2022/06/23 12:17:27 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//Finds and returns the PATH variable from enviornment
//Returned string is without "PATH="
char	*find_paths(char **env)
{
	while (*env)
	{
		if (ft_strncmp("PATH", *env, 4) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

//Prints 'cmd': command not found on stderr
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

//Checks if cmd is in each of the paths
//If succes: path/'cmd' is returned
//If not sucess: NULL is returned
char	*path_finder(char *cmd, char **path_2d)
{
	char	*path;
	char	*temp_path;
	int		i;

	i = 0;
	while (path_2d[i])
	{
		temp_path = ft_strjoin(path_2d[i], "/");
		ft_check_malloc(temp_path);
		path = ft_strjoin(temp_path, cmd);
		ft_check_malloc(path);
		free(temp_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (path_2d[++i])
		free(path_2d[i]);
	free(path_2d);
	return (NULL);
}

//Checks if cmd can be directly found by execve
//If not, cmd is searched in all the different paths
//If access succeeds: execve is called and process terminates
void	execute(char *cmd, char **path_2d, char **envp)
{
	char	**cmd_2d;
	char	*cmd_path;

	cmd_2d = ft_split(cmd, ' ');
	ft_check_malloc(cmd_2d);
	if (access(cmd_2d[0], X_OK) == 0)
	{
		if (execve(cmd_2d[0], cmd_2d, envp) == -1)
			error();
	}
	cmd_path = path_finder(cmd_2d[0], path_2d);
	if (!cmd_path)
		exit_wrong_command(cmd_2d);
	if (execve(cmd_path, cmd_2d, envp) == -1)
		error();
}
