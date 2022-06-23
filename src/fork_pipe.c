/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 11:22:34 by pderksen      #+#    #+#                 */
/*   Updated: 2022/06/23 14:27:04 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//Child process for cmds that are not the last
//Read end (fd[0]) of the pipe is closed
//Write end (fd[1]) is duplicated to STDOUT and closed
//If execute succeeds, child process terminates 
void	child_process(int *fd, char **argv, t_pipex *p)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error();
	close(fd[1]);
	execute(argv[p->current_cmd], p->path_2d, p->envp);
}

//Child process for the last cmd
//fd of out.txt file is duplicated to STDOUT and closed
//If execute succeeds, child process terminates
void	child_process_2(char **argv, t_pipex *p)
{
	if (dup2(p->f2, STDOUT_FILENO) == -1)
		error();
	close(p->f2);
	execute(argv[p->current_cmd], p->path_2d, p->envp);
}

//Closes write end (fd[1]) of the pipe
//read end (fd[0]) of pipe is duplicated to STDIN and closed
//Such that next child process reads input from end of previous pipe
//Waits for the child to be terminated
void	parent_process(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error();
	close(fd[0]);
}

//Waits for the last child process to terminate
//Returns exit status
void	parent_process_2(pid_t child)
{
	int	status;

	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}
