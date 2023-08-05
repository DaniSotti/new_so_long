/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:07:35 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/17 23:23:38 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	strlen;
	char	*sub;

	if (!s)
		return (0);
	j = 0;
	strlen = ft_strlen(s);
	if (len > strlen)
		len = strlen + 1;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (0);
	while (start < strlen && j < len)
	{
		sub[j] = s[start];
		j++;
		start++;
	}
	sub[j] = '\0';
	return (sub);
}

/*int main()
{
    char str[] = "danielle de sotti";
    //char    start = 'de';

    printf("%s", ft_substr(str, 3, 8));
    return (0);
}*/