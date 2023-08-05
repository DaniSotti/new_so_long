/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:58:50 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 23:12:53 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + len);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)(s + len));
		len--;
	}
	return (0);
}

/*int	main(void)
{
	char *src = "abbbbbbbb";
    char *d1 = strrchr(src, 'a');
    char *d2 = ft_strrchr(src, 'a');

	printf("%s", d1);
	printf("%s", d2);
	return (0);
} */