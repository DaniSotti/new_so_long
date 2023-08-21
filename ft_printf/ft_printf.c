/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 23:07:36 by dde-sott          #+#    #+#             */
/*   Updated: 2022/12/12 23:47:23 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_printptr(va_arg(args, size_t), "0123456789abcdef"));
	else if (c == 'd')
		return (print_number(va_arg(args, int)));
	else if (c == 'i')
		return (print_number(va_arg(args, int)));
	else if (c == 'u')
		return (print_number_u(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_putnbrhex(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_putnbrhex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (c == '%')
		return (ft_putchar(c));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;	

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += format(str[i], args);
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end (args);
	return (len);
}
