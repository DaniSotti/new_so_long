/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:33:02 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/18 20:50:06 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/*
int	main()
{
	FILE *fp;
	
	fp = fopen("teste.txt", "w");
	fprintf(fp, "This is my file");
	fclose(fp);
	//colocamos a localizacao e o nome, e no segundo a permissao (r, w)
	char s[] = "Ola";

	ft_putstr_fd(s, 4);
	return(0);
}*/
