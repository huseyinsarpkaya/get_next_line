/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husarpka <husarpka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:19:42 by husarpka          #+#    #+#             */
/*   Updated: 2024/12/09 17:39:23 by husarpka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char *ft_get_buffer(char *buffer)
{
    int i = 0;
    char *newbuffer;
    int a = 0;

    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\n')
    {
        buffer[i] = '\0';
        i++; 
    }
    else
    {
        free(buffer);
        return (NULL);
	}
    newbuffer = malloc(sizeof(char) * (ft_strlen(buffer + i) + 1));
    if (!newbuffer)
        return (NULL);
  
    while (buffer[i] != '\0')
        newbuffer[a++] = buffer[i++];
    newbuffer[a] = '\0'; 
    free(buffer);
    return newbuffer;
}


char	*ft_get_line(char *buffer)
{
	char *result;
	int i;
	char *temp;
	
	i = 0;
	if(!buffer)
		return (NULL);
       
	while (buffer[i] && buffer[i] != '\n')
		i++;
        i++;
	result = malloc(sizeof(char) * (i  + 1));
	if (!result)
		return (NULL);
       
	temp = result;
    
	while(*buffer && i > 0)
    {
		*result++ = *buffer++;
        i--; 
   
    } 
   *result = '\0';
	return (temp);
}
char *ft_get_next(int fd, char *buffer)
{
    char *temp; 
    ssize_t bytes_read;
    
   temp = malloc(BUFFER_SIZE + 1);
    if (!temp)
        return (NULL);
        
    while (1) 
    {
        bytes_read = read(fd, temp, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(temp);
            return (NULL);
        }
        if (bytes_read == 0)
            break;
        temp[bytes_read] = '\0';
       buffer = ft_strjoin(buffer, temp);
       
        if (ft_strchr(temp, '\n'))
            break;
    }
     free(temp);
    return buffer;
}


char	*get_next_line(int fd)
{
	static char	*buffer;
	char *line;
    
	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);	
	buffer = ft_get_next(fd,buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_get_buffer(buffer);
	return (line);
  
}
