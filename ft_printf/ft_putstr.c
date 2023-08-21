/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:02:51 by dde-sott          #+#    #+#             */
/*   Updated: 2022/12/09 22:16:18 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(const char *arg)
{
	int	i;

	i = 0;
	if (!arg)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (arg[i])
	{
		write(1, &arg[i], 1);
		i++;
	}
	return (i);
}
