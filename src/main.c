/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:05:57 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/21 18:00:58 by het-tale         ###   ########.fr       */
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

void	ft_error(char *str)
{
	perror(str);
	exit(0);
}

void	manage_error(t_pipex *pipex)
{
	if (pipex->out_file == -1)
		ft_error("outfile fd");
	if (pipex->in_file == -1)
		perror("infile fd");
	if (pipe(pipex->fd_pipe) == -1)
		ft_error("Pipe");
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc == 5)
	{
		pipex.out_file = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
		pipex.in_file = open(argv[1], O_RDONLY, 0444);
		manage_error(&pipex);
		pipex.child1_id = fork();
		if (pipex.child1_id == 0)
		{
			close(pipex.fd_pipe[0]);
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
