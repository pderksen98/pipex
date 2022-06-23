/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 11:21:23 by pderksen      #+#    #+#                 */
/*   Updated: 2022/06/23 12:26:58 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//Prints error message corresponding to errno 
void	error(void)
{
	perror("Error");
	exit (errno);
}

//Prints Error: "message" on stderr with perror message
void	error_message(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	exit(errno);
}

//The first time the input fd is set to fd of infile(f1)
//While loop until last cmd is found, when not last cmd:
//...a pipe is created else no pipe is needed and output
//...goes to output file
void	pipex(t_pipex p, char **argv)
{
	int		fd[2];
	pid_t	child;

	if (dup2(p.f1, STDIN_FILENO) == -1)
		error();
	close(p.f1);
	while (p.current_cmd != p.last_cmd)
	{
		if (pipe(fd) == -1)
			error();
		child = fork();
		if (child < 0)
			error();
		if (child == 0)
			child_process(fd, argv, &p);
		else
			parent_process(fd, child);
		p.current_cmd++;
	}
	child = fork();
	if (child < 0)
		error();
	if (child == 0)
		child_process_2(argv, &p);
	parent_process_2(child);
}

//Checks if correct number of arguments
//Opens infile and outfile
//Calls find_path function and pipex()
int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	char	*paths;

	if (argc < 5)
	{
		ft_putstr_fd("To few arguments (5 minimum)\n", 2);
		return (EXIT_FAILURE);
	}
	p.f1 = open(argv[1], O_RDONLY);
	p.f2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (p.f1 < 0 || p.f1 > OPEN_MAX)
		error_message(argv[1]);
	if (p.f2 < 0 || p.f2 > OPEN_MAX)
		error_message(argv[argc - 1]);
	p.last_cmd = argc - 2;
	p.current_cmd = 2;
	p.envp = envp;
	paths = find_paths(envp);
	if (paths == NULL)
		error_message("PATH variable not found");
	p.path_2d = ft_split(paths, ':');
	ft_check_malloc(p.path_2d);
	pipex(p, argv);
	return (0);
}
