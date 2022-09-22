/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 07:08:45 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/22 01:02:11 by het-tale         ###   ########.fr       */
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
# define BUFFER_SIZE 42

/*--------------------Program variables----------------------*/
typedef struct s_pipex
{
	int	in_file;
	int	out_file;
	int	*fd_pipe;
	int	status;
	int	*child_pid;
	int	input;
	int	output;
	int	nb_cmd;
	int	cmd_index;
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
int		ft_strchr(char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
/*---------------get_next_line------------------------*/
char	*get_next_line(int fd);
char	*extract_line(char *str);
char	*extract_after_line(char *str);
char	*ft_read(int *rb, char *temp, char *buf, int fd);
char	*ft_cpy(char *str, int *i, int *j);
void	skip_line(char *str, int *j);
/*-------------------Pipex functions-------------------*/
char	*check_command(char *cmd, char *env[]);
void	execute_command(int input, int output, char *cmd, char *env[]);
char	*get_right_path(char *env[], char *cmd);
char	*get_right_path_utils(t_path *corr_path, char *cmd, char *env[]);
void	close_and_free(t_pipex pipex, int n);
void	manage_error(t_pipex *pipex, int n);
void	close_pipes(t_pipex *pipex, int n);
void	ft_error(char *str);
void	input_output(t_pipex *pipex, int i, int n);
void	here_doc_implementation(t_pipex *pipex, int argc, char *argv[]);
void	init_args(t_pipex *pipex, int argc, char *argv[]);
#endif
