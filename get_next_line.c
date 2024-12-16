/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husarpka <husarpka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:19:42 by husarpka          #+#    #+#             */
/*   Updated: 2024/12/14 19:24:41 by husarpka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_get_buffer(char *buffer)
{
	int		i;
	char	*newbuffer;
	int		a;

	if (!buffer)
		return (NULL);
	i = 0;
	a = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	newbuffer = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!newbuffer)
		return (free(buffer), NULL);
	while (buffer[i] != '\0')
		newbuffer[a++] = buffer[i++];
	newbuffer[a] = '\0';
	free (buffer);
	return (newbuffer);
}

static char	*ft_get_line(char *buffer)
{
	char	*result;
	int		i;
	char	*temp;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (free(buffer), NULL);
	temp = result;
	while (*buffer && i > 0)
	{
		*result++ = *buffer++;
		i--;
	}
	*result = '\0';
	return (temp);
}

static char	*ft_get_next(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (2)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(temp), free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			return (free(temp), NULL);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_get_next(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	if (!line)
		return (NULL);
	buffer = ft_get_buffer(buffer);
	return (line);
}
