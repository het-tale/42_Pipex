/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:48:15 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/07 13:56:07 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char *str)
{
	perror(str);
	exit(0);
}

void	usage_error(int argc, char *argv[])
{	
	if (argc < 5)
	{
		if (argc >= 2 && !ft_strncmp(argv[1], "here_doc", 7))
			ft_putstr_fd(2, "Usage: ./pipex here_doc LIMITER c1 ... cn out");
		else
			ft_putstr_fd(2, "Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile");
		exit(0);
	}
	else if (argc < 6 && !ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		ft_putstr_fd(2, "Usage: ./pipex here_doc LIMITER cmd1 ... cmdn out");
		exit(0);
	}
}

void	manage_error(t_pipex *pipex, int n)
{
	int	i;

	i = 0;
	if (pipex->out_file == -1)
		ft_error("outfile fd");
	if (pipex->in_file == -1)
		perror("infile fd");
	while (i < n - 1)
	{	
		if (pipe(pipex->fd_pipe + 2 * i) == -1)
			ft_error("Pipe");
		i++;
	}
}

void	close_and_free(t_pipex pipex, int n)
{
	int	i;

	i = 0;
	close(pipex.in_file);
	close(pipex.out_file);
	unlink("temp_file");
	while (i < (n - 1) * 2)
	{
		close(pipex.fd_pipe[i]);
		i++;
	}
	waitpid(-1, &(pipex.status), 0);
	free(pipex.child_pid);
	free(pipex.fd_pipe);
}

void	close_pipes(t_pipex *pipex, int n)
{
	int	j;

	j = 0;
	while (j < n)
	{
		if (pipex->fd_pipe[j] != pipex->input
			&& pipex->fd_pipe[j] != pipex->output)
			close(pipex->fd_pipe[j]);
		j++;
	}
}
