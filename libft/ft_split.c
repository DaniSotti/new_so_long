/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:58:53 by dde-sott          #+#    #+#             */
/*   Updated: 2022/11/21 23:02:09 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_coutstrs(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == '\0')
				return (count);
		}
		i++;
	}
	return (count);
}

static int	word_len(char const *s, int i, char c)
{
	int	j;

	j = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

static char	*ft_substrncpy(const char	*s, int pos, int len)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[pos];
		i++;
		pos++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strsplit;
	int		i;
	int		j;
	int		len;
	int		countstr;

	i = 0;
	j = 0;
	countstr = ft_coutstrs(s, c);
	strsplit = (char **)malloc((countstr + 1) * sizeof(char *));
	if (!strsplit)
		return (0);
	while (j < countstr)
	{
		len = 0;
		while (s[i] != '\0' && s[i] == c)
				i++;
		len = word_len(s, i, c);
		strsplit[j] = ft_substrncpy(s, i, len);
		j++;
		i = i + len;
	}
	strsplit[j] = NULL;
	return (strsplit);
}

/*int    main()
{
	char    **tab;
	int        i;
	//char    c;
	//c = ' ';
	tab = ft_split("hello!zzzzzzzzdani", 'z');
	i = 0;
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
	}
	return (0);
}*/