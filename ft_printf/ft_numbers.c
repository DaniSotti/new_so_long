/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:13:00 by dde-sott          #+#    #+#             */
/*   Updated: 2022/12/13 00:14:28 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// para transformar um numero inteiro em string
static int	number_len(long long n, int base)
{
	unsigned int	len;

	len = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		len++;
	while (n != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

int	print_number(int nb)
{
	int			len;
	long long	n;

	n = (long long) nb;
	len = number_len(n, 10);
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		print_number(nb / 10);
	}
	ft_putchar(48 + nb % 10);
	return (len);
}

//Transformar o numero em unsigned
int	print_number_u(unsigned int nbu)
{
	int	len;

	len = number_len(nbu, 10);
	if (nbu > 9)
		print_number_u(nbu / 10);
	ft_putchar(48 + nbu % 10);
	return (len);
}

int	ft_printptr(size_t npointer, char *base)
{
	char	hexa[25];
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (npointer == 0)
	{
		write(1, "0x0", 3);
		len += 3;
	}
	else
	{
		write(1, "0x", 2);
		len += 2;
	}
	while (npointer != 0)
	{
		hexa[i++] = base[npointer % 16];
		npointer /= 16;
		len++;
	}
	while (i--)
		ft_putchar(hexa[i]);
	return (len);
}

int	ft_putnbrhex(unsigned int decimal, char *base)
{
	char	hex[25];
	int		len;
	int		i;

	i = 0;
	len = number_len(decimal, 16);
	if (decimal == 0)
		return (ft_putchar('0'));
	while (decimal != 0)
	{
		hex[i++] = base[decimal % 16];
		decimal /= 16;
	}
	while (i--)
		ft_putchar(hex[i]);
	return (len);
}
