/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husarpka <husarpka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:20:57 by husarpka          #+#    #+#             */
/*   Updated: 2024/12/02 12:37:09 by husarpka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
char	*ft_strjoin(char *s1, char *s2)
{
	char	*buffer;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	buffer = malloc(ft_strlen((s1) + ft_strlen(s2) + 1) * sizeof(char));
	if(!buffer)
		return (NULL);
	result = buffer;
	while(*s1)
		*buffer++ = *s1++;
	while(*s2)
		*buffer++ = *s2++;
	*buffer = '\0';
	free(s1);
	return (result); 
}
