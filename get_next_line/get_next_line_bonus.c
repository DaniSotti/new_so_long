/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 21:05:56 by dde-sott          #+#    #+#             */
/*   Updated: 2023/02/11 12:50:54 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*temp;
	int			is_nline;

	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (ft_clean_buffer(buf[fd]));
	temp = NULL;
	is_nline = 0;
	while (!is_nline && (buf[fd][0] || read(fd, buf[fd], BUFFER_SIZE) > 0))
	{
		temp = ft_strjoin(temp, buf[fd]);
		is_nline = ft_is_nline(buf[fd]);
	}
	return (temp);
}

//apagar

/*#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

int main()
{
	int fd = 0;
	char *line1;
	//char *line2;
	
	fd = open("./test.txt", O_RDWR);
	line1 = get_next_line(fd);
	//line2 = get_next_line(fd);
	printf("%s", line1);
	//printf("%s", line2);
	close(fd);
}*/