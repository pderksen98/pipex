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


int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	
	// if (argc < 5)
	// 	return (0);
	char	*envp_path;
	char	**envp_path2d;
	p.f1 = open(argv[1], O_RDONLY);
	p.f2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	
	if (p.f1 < 0 || p.f2 < 0 || p.f1 > OPEN_MAX || p.f2 > OPEN_MAX)
	{
		perror("");
		exit(errno);
	}
	envp_path = get_envp_path(envp);
	envp_path2d = ft_split(envp_path, ':');
	ft_check_malloc(envp_path2d);
	
	
	return (0);
}
