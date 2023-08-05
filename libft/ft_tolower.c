/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:00:37 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 22:14:15 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

/*
//Nao enviar
#include <stdio.h>
int main()
{
    char str[] = "PIZZA123";
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        str[i] = ft_tolower(str[i]);
        i++;
    }
    printf("%s", str);
    return(0);
}*/