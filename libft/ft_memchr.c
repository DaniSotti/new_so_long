/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:24:47 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 23:53:58 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str_s;
	size_t	i;

	str_s = (char *) s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char) str_s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

/*#include <stdio.h>
int main()
{
    char str[] = "danidesotti@gmail.com";
    char *domain = ft_memchr(str, '.', 20);
    char *domainreal = memchr(str, '.', 20);
    printf("domain: %s\n", domainreal);
    printf("domain: %s\n", domain);
    return (0);
}*/
