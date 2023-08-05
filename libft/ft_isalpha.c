/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:59:17 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 00:26:35 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/*//Não enviar
#include<ctype.h>
#include<stdio.h>
int main()
{
    char c = 'A';
    if (isalpha(c))
        printf("É uma letra\n");
    else
        printf("Não é uma letra\n");
    if (ft_isalpha(c))
        printf("É uma letra");
    else
        printf("Não é uma letra");
    return (0);
}*/