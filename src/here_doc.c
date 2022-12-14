/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:28:57 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/07 13:48:26 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_args(t_pipex *pipex, int argc, char *argv[])
{
	int	ac;

	ac = argc - 1;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		here_doc_implementation(pipex, argc, argv);
	else
	{
		pipex->out_file = open(argv[ac], O_CREAT | O_TRUNC | O_RDWR, 0777);
		pipex->in_file = open(argv[1], O_RDONLY, 0444);
		pipex->nb_cmd = argc - 3;
		pipex->cmd_index = 2;
	}
	pipex->fd_pipe = malloc(sizeof(int) * (pipex->nb_cmd - 1) * 2);
	pipex->child_pid = malloc(sizeof(int) * pipex->nb_cmd);
	manage_error(pipex, pipex->nb_cmd);
}

void	here_doc_implementation(t_pipex *pipex, int argc, char *argv[])
{
	int		temp_fd;
	char	*line;

	temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_APPEND, 0644);
	line = "";
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (!ft_strncmp(argv[2], line, ft_strlen(argv[2]))
			&& (ft_strlen(argv[2]) + 1) == ft_strlen(line))
		{
			free(line);
			break ;
		}
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
	close(temp_fd);
	pipex->out_file = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	pipex->in_file = open("temp_file", O_RDONLY, 0444);
	pipex->nb_cmd = argc - 4;
	pipex->cmd_index = 3;
}
