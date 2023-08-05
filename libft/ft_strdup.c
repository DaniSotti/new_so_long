/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:25:49 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/07 21:39:46 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstr;
	size_t	i;

	newstr = (char *) malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!newstr)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

/*int main(int argc, char **argv)
{
    char *mine;
    char *theirs;

    if (argc == 2)
    {
        mine = ft_strdup(argv[1]);
        theirs = strdup(argv[1]);
        printf(":%s:\n:%s:\n", mine, theirs);
    }
    return (0);
}*/