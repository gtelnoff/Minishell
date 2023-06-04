/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:17:41 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/02 16:17:44 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*str;
	size_t	i;

	if (elementCount > 2147483647 || elementSize > 2147483647 \
		|| elementCount * elementSize > 2147483647)
		return (NULL);
	i = -1;
	str = malloc(elementCount * elementSize);
	if (!str)
		return (NULL);
	while (++i < (elementCount * elementSize))
		str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sbis;
	char	*dest;
	size_t	i;
	size_t	j;

	sbis = (char *)s;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		dest = malloc(sizeof(char) * 1);
		*dest = '\0';
		return (dest);
	}
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = start;
	while (i < len)
		dest[i++] = sbis[j++];
	dest[i] = '\0';
	return (dest);
}

int	countab(char const *s, char c)
{
	int	i;
	int	ntab;

	i = 0;
	ntab = 0;
	while ((size_t)i < ft_strlen(s) && s[i] == c)
		i++;
	while ((size_t)i < ft_strlen(s) && s[i])
	{
		if ((s[i] == c && s[i + 1] != c) || s[i + 1] == '\0')
			ntab++;
		i++;
	}
	return (ntab);
}

unsigned int	countchar(char const *s, char c, unsigned int x)
{
	unsigned int	i;

	i = 0;
	while (s[x] != c && s[x] != '\0')
	{
		i++;
		x++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	index;
	unsigned int	ntab;

	if (!s)
		return (NULL);
	ntab = countab(s, c);
	tab = ft_calloc(sizeof(char *), (ntab + 1));
	if (!tab)
		return (NULL);
	i = 0;
	index = 0;
	while (ntab > 0)
	{
		while (s[i] == c)
			i++;
		tab[index] = ft_substr(s, i, countchar(s, c, i));
		while (s[i] != c && s[i] != '\0')
			i++;
		ntab--;
		index++;
	}
	return (tab);
}
