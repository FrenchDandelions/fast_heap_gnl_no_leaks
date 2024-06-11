/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:17:48 by thole             #+#    #+#             */
/*   Updated: 2024/06/11 01:19:24 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	int		bytes_read;
	char	*buffer;
	char	*new_line;
	size_t	size_buffer;
	int		status;
	char	*s;
	char	*temp;
	char	*pos_nl;
}			t_gnl;

void		*free_buffer(void) __attribute__((destructor));
void		*free_struct(t_gnl *gnl);
char		*get_next_line(int fd);
t_gnl		*singleton_gnl(void);
size_t		ft_strlen(const char *s);
char		*ft_strchr(t_gnl *gnl, int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_freestrjoin(char *s1, char *s2, size_t size);

#endif
