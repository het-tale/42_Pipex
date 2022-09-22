/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:05:57 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/22 01:10:30 by het-tale         ###   ########.fr       */
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
	int		index;

	init_args(&pipex, argc, argv);
	i = 0;
	while (i < pipex.nb_cmd)
	{
		index = i + pipex.cmd_index;
		input_output(&pipex, i, pipex.nb_cmd);
		pipex.child_pid[i] = fork();
		if (pipex.child_pid[i] == 0)
		{
			close_pipes(&pipex, (pipex.nb_cmd - 1) * 2);
			execute_command(pipex.input, pipex.output, argv[index], env);
		}
		i++;
	}
	close_and_free(pipex, pipex.nb_cmd);
}
