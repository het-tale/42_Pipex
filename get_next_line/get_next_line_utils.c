/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 07:25:45 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/21 23:40:21 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	skip_line(char *str, int *j)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
		(*j)++;
	}
}

char	*extract_line(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (str[i] == '\0')
		return (NULL);
	skip_line(str, &j);
	line = malloc((j + 2) * sizeof(char));
	i = 0;
	while (str[i] != '\0')
	{
		line[i] = str[i];
		if (str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*ft_cpy(char *str, int *i, int *j)
{
	int		k;
	int		l;
	char	*line;

	k = *i;
	l = 0;
	line = malloc((*j + 1) * sizeof(char));
	while (str[k] != '\0')
	{
		line[l] = str[k];
		l++;
		k++;
	}
	line[l] = 0;
	*i = k;
	*j = l;
	free(str);
	return (line);
}

char	*extract_after_line(char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	skip_line(str, &i);
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	k = i;
	while (str[k] != '\0')
	{
		k++;
		j++;
	}
	return (ft_cpy(str, &i, &j));
}
