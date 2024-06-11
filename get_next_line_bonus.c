/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:22:38 by thole             #+#    #+#             */
/*   Updated: 2024/06/11 14:22:39 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (!s[i + 1])
			return (i + 1);
		else if (!s[i + 2])
			return (i + 2);
		else if (!s[i + 3])
			return (i + 3);
		else if (!s[i + 4])
			return (i + 4);
		else if (!s[i + 5])
			return (i + 5);
		else if (!s[i + 6])
			return (i + 6);
		else if (!s[i + 7])
			return (i + 7);
		else if (!s[i + 8])
			return (i + 8);
		i += 8;
	}
	return (i);
}

char	*ft_read(int fd, t_gnl *gnl)
{
	if (!gnl->buffer[gnl->fd])
	{
		gnl->buffer[gnl->fd] = malloc(sizeof(char) * 1);
		*(gnl->buffer[gnl->fd]) = '\0';
	}
	gnl->s = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!gnl->s || !gnl->buffer[gnl->fd])
		return (free_struct(gnl));
	gnl->bytes_read = 1;
	while (!ft_strchr(gnl, '\n') && gnl->bytes_read > 0)
	{
		gnl->bytes_read = read(fd, gnl->s, BUFFER_SIZE);
		if (gnl->bytes_read == -1)
			return (free_struct(gnl));
		else if (gnl->bytes_read == 0)
			break ;
		gnl->s[gnl->bytes_read] = '\0';
		gnl->size_buffer += gnl->bytes_read;
		gnl->buffer[gnl->fd] = ft_freestrjoin(gnl->buffer[gnl->fd], gnl->s,
				gnl->size_buffer);
		if (!gnl->buffer[gnl->fd])
			return (free_struct(gnl));
	}
	(free(gnl->s), gnl->s = NULL);
	return (NULL);
}

char	*ft_new_line(t_gnl *gnl)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!gnl->buffer[gnl->fd][i])
		return (NULL);
	i = gnl->size_buffer;
	if (gnl->pos_nl)
		i = gnl->pos_nl - (gnl->buffer[gnl->fd]) + 1;
	new_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!new_line)
		return (free_struct(gnl));
	i = 0;
	while (gnl->buffer[gnl->fd][i] && gnl->buffer[gnl->fd][i] != '\n')
	{
		new_line[i] = gnl->buffer[gnl->fd][i];
		i++;
	}
	if (gnl->buffer[gnl->fd][i] && gnl->buffer[gnl->fd][i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

char	*ft_delete_past_line(t_gnl *gnl)
{
	char	*trimmed_line;
	int		i;
	int		j;

	i = 0;
	i = gnl->size_buffer;
	if (gnl->pos_nl)
		i = gnl->pos_nl - (gnl->buffer[gnl->fd]);
	if (!gnl->buffer[gnl->fd][i])
		return (free(gnl->buffer[gnl->fd]), gnl->buffer[gnl->fd] = NULL);
	trimmed_line = (char *)malloc(sizeof(char) * (gnl->size_buffer - i + 1));
	if (!trimmed_line)
		return (free_struct(gnl));
	i++;
	j = 0;
	while (gnl->buffer[gnl->fd][i])
		trimmed_line[j++] = gnl->buffer[gnl->fd][i++];
	free(gnl->buffer[gnl->fd]);
	gnl->buffer[gnl->fd] = NULL;
	trimmed_line[j] = '\0';
	return (trimmed_line);
}

char	*get_next_line(int fd)
{
	t_gnl	*gnl;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	gnl = singleton_gnl();
	gnl->new_line = NULL;
	gnl->fd = fd;
	gnl->size_buffer = ft_strlen(gnl->buffer[gnl->fd]);
	ft_read(fd, gnl);
	if (gnl->status)
		return (free_struct(gnl));
	gnl->new_line = ft_new_line(gnl);
	if (gnl->status)
		return (free_struct(gnl));
	gnl->buffer[gnl->fd] = ft_delete_past_line(gnl);
	if (gnl->status)
		return (free_struct(gnl));
	return (gnl->new_line);
}

int	main(void)
{
	int		fd;
	int		fd2;
	char	*str;

	fd = open("bible.txt", O_RDONLY);
	if (fd == -1)
		return (2);
	fd2 = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (2);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	while ((str = get_next_line(fd2)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	close(fd2);
	return (0);
}
