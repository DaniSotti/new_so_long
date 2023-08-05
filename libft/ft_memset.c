/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:00:00 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 21:20:27 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*d;

	d = (char *)b;
	while (len > 0)
	{
		d[len - 1] = c;
		len--;
	}
	return (b);
}

//Nao enviar
/*#include <stdio.h>

int main()
{
    char buffer[10];

    ft_memset(buffer, 'a', sizeof(char) *10);

    for (int i = 0; i < 10; i++)
        printf("%c", buffer[i]);
    printf("\n");

    return (0);
}*/