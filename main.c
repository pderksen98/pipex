/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/07 14:13:39 by pderksen      #+#    #+#                 */
/*   Updated: 2022/05/11 18:32:01 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_message(char *message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}




void	pipex(int f1, int f2)
{
	int end[2];
	pid_t	parent;
	pipe(end);
	parent = fork();
	if (parent < 0)
		exit_message("Fork error");
	if (!parent) //child process
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}

void	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;
	
	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child_one(f1, cmd1);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child_two(f2, cmd2);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}
	

# child_process(f1, cmd1)
{
	//add protection if dup2() < 0
	// dup2 close stdin, f1 becomes the new stdin
	dup2(f1, STDIN_FILENO); //we ant f1 to be execve() input
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(f1);
	//execve function for each possible path
	//if succesful here the child will terminate otherwise exit_failure
	exit(EXIT_FAILURE);
}

//Parent process in pseude code will be similar, but with waitpid() at the very beginning 
//to wait for the child to finish her process
# parent_process(f2, cmd2)
{
	waitpid(-1, &status, 0);
	dup2(f2, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	//add protection if dup2() < 0
	close(end[1]);
	close(f2);
	//execve function for each possible path
	exit(EXIT_FAILURE);
}
	

// int execve(const char *path, char *const argv[], char *envp[])

// path: the path to our command
//		 type 'which ls' and 'which wc in your terminal
//		  you'll see the exact path to the commands binaries

// argv[]: the args the command needs, for ex: 'ls -la'
//	     	you can use uour ft_split to obtain a char **
//          like this {"ls", "-la", NULL}
//  		it must be NULL terminated
	
// envp: the environmental variable
// 		 you can simply retrieve it in your main (see below)
//        and pass int onto execve, no need to do anything here
//		in envp you'll see a line PATH which contains all possible
//		paths to the commands binareis

int main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;

	f1 = open(argv[1], O_RDONLY]);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	//O_TRUNC say that if the file does exist, to "truncate" it to zero bytes, erasing wat was there
	if (f1 < 0 || f2 < 0)
	{
		perror();
		exit(errno);
	}
		return (-1);
	pipex(f1, f2, argv, envp);
	return (0);
}

// to see what is inside the envp, type env in your terminal
// after PATH are all the possible paths to the command binaries
// split them with : as delimiter
// execve will have to try every possible path to the cmd until it finds the good one
// If the command does not exist, execve will do nothing and return -1
// else, it will execute the cmd, delete all ongoing processes (no free or exit needed


char	*path_from_envp;
char	**mypaths;
char	**mycmdargs;

//retrieve the line PATH from envp
path_from_envp = ft_substr(envp ....);
mypaths = ft_split(path_from_envp, ":");
mycmdargs = f_split(argv[2], " ");

//in your child or parent process

int		i;
char *cmd;
i = -1;
while (mypaths[++i])
{
	cmd = ft_join(mypaths[i], argv[2]); //protect your ft_join
	execve(cmd, mycmdargs, envp); //if execve succeeds, it exits
	// perror("Error"); <- add perror to debug
	free(cmd) // if execve fails, we free and we try a new path
}
return (EXIT_FAILURE);
