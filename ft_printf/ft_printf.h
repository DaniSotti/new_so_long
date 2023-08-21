/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:23:36 by dde-sott          #+#    #+#             */
/*   Updated: 2022/12/13 00:15:18 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_putstr(const char *arg);
int		ft_printf(const char *str, ...);
int		ft_putnbrhex(unsigned int n, char *base);
int		ft_putchar(int c);
int		ft_printptr(size_t npointer, char *base);
int		print_number(int nb);
int		print_number_u(unsigned int nbu);

#endif