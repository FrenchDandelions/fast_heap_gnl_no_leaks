/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:25:17 by thole             #+#    #+#             */
/*   Updated: 2024/06/11 01:32:38 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	int		i;

	i = 0;
	ch = c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

t_gnl *singleton_gnl(void)
{
    static t_gnl gnl = {0};

    gnl.new_line = NULL;
    return(&gnl);
}

void *free_buffer(void)
{
    t_gnl *gnl;
    gnl = singleton_gnl();
    if(gnl->buffer[gnl->fd])
        (free(gnl->buffer[gnl->fd]), gnl->buffer[gnl->fd] = NULL);
    if(gnl->new_line)
        (free(gnl->new_line), gnl->new_line = NULL);
    if(gnl->s)
        (free(gnl->s), gnl->s = NULL);
    gnl->status = 1;
    return(NULL);
}

char	*ft_freestrjoin(char *s1, char *s2, size_t size)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	free(s1);
	return (str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
    unsigned char    *ptr2;
    size_t n;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
    ptr2 = (unsigned char*) ptr;
    n = nmemb * size;
	while (n > 0)
	{
		*ptr2++ = '\0';
		n--;
	}
	return (ptr);
}
