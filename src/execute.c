/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:32:48 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/21 22:22:13 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_command(int input, int output, char *cmd, char *env[])
{
	char	*right_path;
	char	**exec;

	if (dup2(input, 0) == -1)
		ft_error("Redirecting input error");
	if (dup2(output, 1) == -1)
		ft_error("Redirecting output error");
	exec = ft_split(cmd, ' ');
	right_path = check_command(exec[0], env);
	if (!right_path)
		exit(1);
	execve(right_path, exec, env);
	close(output);
}

char	*get_right_path_utils(t_path *corr_path, char *cmd, char *env[])
{
	corr_path->d = 1;
	corr_path->len = ft_strlen(env[corr_path->i]);
	corr_path->path = ft_substr(env[corr_path->i], 5, corr_path->len - 5);
	corr_path->split = ft_split(corr_path->path, ':');
	corr_path->j = 0;
	while (corr_path->split[corr_path->j])
	{
		corr_path->path = ft_strjoin(corr_path->split[corr_path->j], "/");
		corr_path->path = ft_strjoin(corr_path->path, cmd);
		if (access(corr_path->path, F_OK) == 0)
			return (corr_path->path);
		corr_path->j++;
	}
	return (NULL);
}

char	*get_right_path(char *env[], char *cmd)
{
	t_path	corr_path;

	corr_path.i = 0;
	corr_path.len = 0;
	corr_path.d = 0;
	while (env[corr_path.i])
	{
		if (!ft_strncmp(env[corr_path.i], "PATH=", 5))
			corr_path.path = get_right_path_utils(&corr_path, cmd, env);
		if (corr_path.d == 1)
			break ;
		corr_path.i++;
	}
	return (corr_path.path);
}

char	*check_command(char *cmd, char *env[])
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (get_right_path(env, cmd));
}
