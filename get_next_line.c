/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husarpka <husarpka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:19:42 by husarpka          #+#    #+#             */
/*   Updated: 2024/12/02 16:47:17 by husarpka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*ft_get_next_line(int fd)
{
	int	i;
	char	*buffer;
	char	temp[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*line;

	line = NULL;
	buffer ="";
	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	while ((bytes_read = read(fd, temp, BUFFER_SIZE)) > 0)
	{
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer,temp);
		while (buffer && buffer[0])
		{
		i = 0;
		while (buffer[i] && buffer[i] != '\0')
			i++;
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			line = ft_strjoin(line,buffer);
			buffer = &buffer[i + 1];
			return (line);
		}
		
		if (bytes_read == 0)
			break;
	}
	}
	if (bytes_read == 0 && buffer && buffer[0])
	{
		line = ft_strjoin(line, buffer);
		free(buffer);
		return (line);
	}
	
	free(buffer);
	return (NULL);
		
}


#include <stdio.h>


int main()
{
    int fd;
    char *line;
    fd = open("test.text", O_RDONLY);
    if (fd < 0)
        return 1;

    // Satır satır oku ve yazdır
    while ((line = ft_get_next_line(fd)) != NULL)
    {
        printf("%s\n", line); // Satırı yazdır
        free(line); // Satırı serbest bırak
    }

    // Dosyayı kapat
   close(fd);
    return 0;
}
