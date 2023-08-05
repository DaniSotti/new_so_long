/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:03:55 by dde-sott          #+#    #+#             */
/*   Updated: 2023/02/11 13:16:47 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			i;
	int			j;
	int			is_nline;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (ft_clean_buffer(buffer));
	temp = NULL;
	is_nline = 0;
	while (!is_nline && (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0))
	{
		temp = ft_strjoin(temp, buffer);
		i = 0;
		j = 0;
		while (buffer[i])
		{
			if (is_nline)
				buffer[j++] = buffer[i];
			if (buffer[i] == '\n')
				is_nline = 1;
			buffer[i++] = 0;
		}
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
