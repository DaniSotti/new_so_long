/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:59:07 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 00:23:11 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int car)
{
	if ((car >= '0' && car <= '9') || (car >= 'a' && car <= 'z')
		|| (car >= 'A' && car <= 'Z'))
		return (1);
	else
		return (0);
}

/*//Nao enviar
#include <stdio.h>
#include <ctype.h>
int main()
{
    char car = '*';

    if (ft_isalnum(car))
        printf("Is a alphanumeric\n");
    else
        printf("Is not a alphanumeric\n");

    if (isalnum(car))
        printf("Is a alphanumeric\n");
    else
        printf("Is not a alphanumeric\n");
    return (0);
}*/