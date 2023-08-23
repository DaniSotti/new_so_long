/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 22:38:25 by dde-sott          #+#    #+#             */
/*   Updated: 2023/02/11 12:25:57 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

 int	count_str(char *str)
 {
 	int	i;

 	i = 0;
 	if (!str)
 		return (0);
 	while (str[i] && str[i] != '\n')
 		i++;
 	if (str[i] == '\n')
 		i++;
 	return (i);
 }

char	*ft_joinstr(char *temp, char *buffer)
{
 	char	*newstr;
 	int		i;
 	int		j;

 	newstr = malloc(count_str(temp) + count_str(buffer) + 1);
 	i = 0;
 	j = 0;
 	if (!newstr)
 		return (NULL);
 	while (temp && temp[i])
 		newstr[j++] = temp[i++];
 	free (temp);
 	i = 0;
 	while (buffer && buffer[i])
 	{
 		newstr[j++] = buffer[i];
 		if (buffer[i++] == '\n')
 			break ;
 	}
 	newstr[j] = '\0';
 	return (newstr);
 }

char	*ft_clean_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		buffer[i++] = 0;
	return (NULL);
}
