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

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*buffer;
	char		*line;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE +1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	bytes_read = read(fd, 0, 0);
	if ( bytes_read < 0)
	{
		free(buffer);
		free (left_c);
		buffer = NULL;
		left_c = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = _fill_line_buffer(fd, left_c, buffer);
	free(buffer);
	if (!line)
		return (NULL);
	left_c = _set_line(line);
	return (line);
}

char	*_fill_line_buffer(int fd,char *left_c,char *buffer)
{
	int	bytes_read;
	int	newline;
	
	newline = 0;
	while(!newline)
	{
	bytes_read = read (fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	if (left_c != NULL)
	{
		left_c = realloc(left_c, ft_strlen(left_c) + bytes_read + 1);
		ft_strcat(left_c, buffer);
	}
		else
			left_c = ft_strdup(buffer);
		if (ft_strchr(buffer, '\n') != NULL)
			newline = 1;
	}
	return (left_c);
}

char	*_set_line(char *line_buffer)
{

	char	*left_c;
	int	i;

	left_c = NULL;
	i = 0;
	if (!line_buffer)
		return (NULL);
	while (line_buffer[i] != '\n' || line_buffer[i] != '\0' )
		i++;
	left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (left_c[0] == 0)
	{
		free(left_c);
		left_c = NULL;
	}
	line_buffer[i + 1] = 0;
	return (left_c);
}
char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
