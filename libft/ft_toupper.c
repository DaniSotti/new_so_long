/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:00:44 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 22:17:25 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

/*//Não enviar

#include <stdio.h>
int main()
{
    char name[] = "PizzaAAAAaAaAaA";
    int i;

    i = 0;
    while (name[i] != '\0')
    {
        name[i] = ft_toupper(name[i]);
        i++;
    }
    printf("%s", name);
    return(0);
}*/