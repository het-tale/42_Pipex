/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 07:08:45 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/21 17:41:14 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

/*--------------------Program variables----------------------*/
typedef struct s_pipex
{
	int	in_file;
	int	out_file;
	int	fd_pipe[2];
	int	status;
	int	child1_id;
	int	child2_id;
}	t_pipex;

typedef struct s_path
{
	int		i;
	int		j;
	char	**split;
	size_t	len;
	char	*path;
	int		d;
}	t_path;

/*---------------libft_functions----------------------------*/
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
/*-------------------Pipex functions-------------------*/
char	*check_command(char *cmd, char *env[]);
void	execute_command(int input, int output, char *cmd, char *env[]);
char	*get_right_path(char *env[], char *cmd);
char	*get_right_path_utils(t_path *corr_path, char *cmd, char *env[]);
void	close_and_free(t_pipex pipex);
#endif
