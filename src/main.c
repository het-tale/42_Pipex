/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:05:57 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/21 21:52:52 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	input_output(t_pipex *pipex, int i, int n)
{
	if (i == 0)
		pipex->input = pipex->in_file;
	else
		pipex->input = pipex->fd_pipe[(2 * i) - 2];
	if (i == n - 1)
		pipex->output = pipex->out_file;
	else
		pipex->output = pipex->fd_pipe[(2 * i) + 1];
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		i;
	int		n;

	pipex.fd_pipe = malloc(sizeof(int) * (argc - 4) * 2);
	pipex.child_pid = malloc(sizeof(int) * (argc - 3));
	i = 0;
	n = argc - 3;
	pipex.out_file = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	pipex.in_file = open(argv[1], O_RDONLY, 0444);
	manage_error(&pipex, n);
	while (i < n)
	{
		input_output(&pipex, i, n);
		pipex.child_pid[i] = fork();
		if (pipex.child_pid[i] == 0)
		{
			close_pipes(&pipex, (argc - 4) * 2);
			execute_command(pipex.input, pipex.output, argv[i + 2], env);
		}
		i++;
	}
	close_and_free(pipex, n);
}
