/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/07 14:13:39 by pderksen      #+#    #+#                 */
/*   Updated: 2022/05/10 17:53:22 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_message(char *message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}

int	main(int argc, char **argv)
{
	if (argc != 5)
		exit_message("Not 4 input arguments\n");
	argv = NULL;
	return (0);	
}
