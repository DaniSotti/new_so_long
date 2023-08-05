/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:25:37 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/18 21:28:50 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	len;

	if (!dest && !src)
		return (0);
	if (src < dest)
	{
		len = n;
		while (len > 0)
		{
			len--;
			((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
		}
	}
	else
	{
		len = 0;
		while (len < n)
		{
			((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
			len++;
		}
	}
	return (dest);
}

/*int main()
{
    char src[] = "string antiga";
    char dest[] = "string nova nossa";

    printf("string antiga: %s\n string nova: %s\n", src, dest);
    ft_memmove(dest, src, sizeof(char) * 14);
    printf("string antiga: %s\n string nova: %s\n", src, dest);
    return (0);
}*/