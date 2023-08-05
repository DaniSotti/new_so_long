/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:25:04 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 00:53:54 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	i = 0;
	str1 = (char *) s1;
	str2 = (char *) s2;
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		}
		i++;
	}
	return (0);
}

/*#include <stdio.h>
int main()
{
    char str1[] = "Danolle";
    char str2[] = "Danielle";

    printf("%i\n", ft_memcmp(str1, str2, 4));
    printf("%i\n", memcmp(str1, str2, 4));
    return (0);
}*/