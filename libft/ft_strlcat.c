/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:00:13 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 21:54:03 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	b;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	a = ft_strlen(dst);
	b = 0;
	while (src[b] != '\0' && a + 1 < dstsize)
	{
		dst[a] = src[b];
		a++;
		b++;
	}
	dst[a] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[b]));
}
/*//Nao enviar
#include "libft.h"
#include<stdio.h>
int main()
{
	char src[] = "Danielle";
	char dst[] = "de Sotti";
	size_t res = ft_strlcat(dst, src, 16);

	printf("%s\n%ld", dst, res);
	return (0);
}*/