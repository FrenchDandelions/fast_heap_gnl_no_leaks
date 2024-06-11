/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:20:19 by thole             #+#    #+#             */
/*   Updated: 2024/06/11 14:20:23 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(t_gnl *gnl, int c)
{
	char	ch;
	int		i;

	i = 0;
	ch = c;
	while (gnl->buffer[gnl->fd][i])
	{
		if (gnl->buffer[gnl->fd][i] == ch)
			return (gnl->pos_nl = (char *)gnl->buffer[gnl->fd] + i);
		i++;
	}
	return (gnl->pos_nl = NULL);
}

t_gnl	*singleton_gnl(void)
{
	static t_gnl	gnl = {0};

	return (&gnl);
}

void	*free_buffer(void)
{
	t_gnl	*gnl;

	gnl = singleton_gnl();
	gnl->fd = 0;
	while (gnl->fd < 1025)
	{
		free(gnl->buffer[gnl->fd]);
		gnl->buffer[gnl->fd] = NULL;
		gnl->fd++;
	}
	if (gnl->s)
		(free(gnl->s), gnl->s = NULL);
	return (NULL);
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

void	*free_struct(t_gnl *gnl)
{
	if (gnl->buffer[gnl->fd])
		(free(gnl->buffer[gnl->fd]), gnl->buffer[gnl->fd] = NULL);
	if (gnl->new_line)
		(free(gnl->new_line), gnl->new_line = NULL);
	if (gnl->s)
		(free(gnl->s), gnl->s = NULL);
	gnl->status = 1;
	return (NULL);
}
