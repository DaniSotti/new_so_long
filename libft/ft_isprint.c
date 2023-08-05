/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:59:46 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 00:36:27 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int car)
{
	if (car >= 32 && car <= 126)
		return (1);
	else
		return (0);
}

/*//Nao enviar
#include<stdio.h>
#include<ctype.h>
int main()
{
    char car = 31;

    if (ft_isprint(car))
        printf("Is printable");
    else
        printf("Is not printable");
    return(0);
}*/