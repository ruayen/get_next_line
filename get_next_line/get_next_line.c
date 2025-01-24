/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raissaou <raissaou@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-20 11:17:16 by raissaou          #+#    #+#             */
/*   Updated: 2025-01-20 11:17:16 by raissaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_memory(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free_memory(&left_c);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (left_c == NULL)
			left_c = ft_strdup("");
		temp = left_c;
		left_c = ft_strjoin(temp, buffer);
		free_memory(&temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_c);
}

char	*_set_line(char *line_buffer)
{
	char	*left_c;
	size_t	i;

	left_c = NULL;
	i = 0;
	if (!line_buffer)
		return (NULL);
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0' )
		i++;
	if (line_buffer[i] == '\n')
	{
		left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
		line_buffer[i + 1] = '\0';
	}
	else
		left_c = NULL;
	return (left_c);
}

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*buffer;
	char		*line;
	char		*temp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer || fd < 0 || BUFFER_SIZE <= 0)
	{
		free_memory(&buffer);
		free_memory(&left_c);
		return (NULL);
	}
	if (left_c == NULL || !ft_strchr(left_c, '\n'))
		left_c = _fill_line_buffer(fd, left_c, buffer);
	free_memory(&buffer);
	if (!left_c)
		return (NULL);
	line = ft_substr(left_c, 0, ft_strchr(left_c, '\n') - left_c + 1);
	temp = left_c;
	left_c = _set_line(left_c);
	free_memory(&temp);
	return (line);
}
