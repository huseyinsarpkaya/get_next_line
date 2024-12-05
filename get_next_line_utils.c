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

#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
    if(!str)
        return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*result;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	result = str;
	while (*s1)
	{
		*str = *s1;
		s1++;
		str++;
	}
	*str = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
char *ft_strjoin(char *s1, char *s2) {
    char *result;
    char *buffer;
    int i = 0; // Başlatma
    int a = 0; // Başlatma

    // Null kontrolü
    if (!s1 && !s2) return NULL;
    if (!s1) return ft_strdup(s2); // Sadece s2'yi döndür
    if (!s2) return ft_strdup(s1); // Sadece s1'i döndür

    // s1'in uzunluğunu hesapla
    while (s1[i])
        i++;
    
    // s2'nin uzunluğunu hesapla
    while (s2[a])
        a++;

    // Bellek tahsis et
    buffer = malloc(i + a + 1);
    if (!buffer)
        return NULL;

    result = buffer; // Sonucu sakla

    // s1'i kopyala
    while (*s1)
        *buffer++ = *s1++;
    
    // s2'yi kopyala
    while (*s2)
        *buffer++ = *s2++;
    
    *buffer = '\0'; // Null terminator ekle
    free(s1);
    return result; // Sonucu döndür
}