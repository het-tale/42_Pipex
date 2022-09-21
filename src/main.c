/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:05:57 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/21 17:21:42 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_and_free(t_pipex pipex)
{
	close(pipex.in_file);
	close(pipex.out_file);
	close(pipex.fd_pipe[0]);
	close(pipex.fd_pipe[1]);
	waitpid(-1, &(pipex.status), 0);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc == 5)
	{
		pipex.out_file = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (pipex.out_file == -1)
			perror("outfile fd");
		if (pipe(pipex.fd_pipe) == -1)
			perror("Pipe");
		pipex.child1_id = fork();
		if (pipex.child1_id == 0)
		{
			close(pipex.fd_pipe[0]);
			pipex.in_file = open(argv[1], O_RDONLY, 0444);
			execute_command(pipex.in_file, pipex.fd_pipe[1], argv[2], env);
		}
		else if (pipex.child1_id != 0)
			pipex.child2_id = fork();
		if (pipex.child2_id == 0)
		{
			close(pipex.fd_pipe[1]);
			execute_command(pipex.fd_pipe[0], pipex.out_file, argv[3], env);
		}
		close_and_free(pipex);
	}
}
