/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:24:29 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 00:08:02 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	totalcount;
	void	*memall;

	totalcount = count * size;
	memall = malloc(totalcount);
	if (memall == NULL)
		return (0);
	else
		ft_memset(memall, 0, totalcount);
	return (memall);
}

/*int main()
{
    //int *original;
    int *mine;
    //original = (int *) calloc(6, sizeof(int));
    mine = (int *) ft_calloc(6, sizeof(int));

    for (int i = 0; i < 6; i++)
        //printf("%i", original[i]);
        printf("%i", mine[i]);

    return (0);
}*/