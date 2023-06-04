/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:59:21 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/13 14:55:09 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [utils02.c]
// int	ft_strlen_parsing(const char *s);
// char	*ft_strnstr(const char *big, const char *little, size_t len);
// void	*ft_calloc_parsing(size_t nmemb, size_t size);
// void	ft_bzero(void *s, size_t n);
// int	ft_strcmp(char *s1, char *s2);
// ------------------PROTOTYPE POUR LE ".h"------------------

int	ft_strlen_parsing(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	m;

	i = 0;
	if (*little == '\0' || little == NULL)
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (little[0] == big[i])
		{
			m = 0;
			while (little[m] == big[i + m] && i + m < len)
			{
				m++;
				if (little[m] == '\0')
					return ((char *)big + i);
			}
		}
		i++;
	}
	return (NULL);
}

void	*ft_calloc_parsing(size_t nmemb, size_t size)
{
	void	*str;

	if (nmemb >= 9223372036854775807 || size >= 9223372036854775807)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	ft_bzero(str, (nmemb * size));
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
