/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:38:35 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/10 17:38:36 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	get_len_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char	*make_1d_array(char **array)
{
	int		i;
	char	*str;

	i = 0;
	while (array[i] != NULL)
	{
		if (i == 0)
		{
			str = array[i];
			i++;
		}
		else
		{
			str = ft_strjoin(str, array[i], i);
			i++;
		}
	}
	return (str);
}

static int	start(char s1, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (s1 == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*dest;
	size_t	i;
	size_t	a;
	size_t	lenmax;

	i = -1;
	a = 0;
	if (!s1)
		return (NULL);
	lenmax = ft_strlen(s1);
	while (start(s1[++i], set))
		a++;
	while (start(s1[lenmax - 1], set))
		--lenmax;
	if (s1[a] == 0 && a > lenmax)
		a = lenmax;
	dest = malloc(sizeof(char) * (lenmax - a + 1));
	if (!dest)
		return (0);
	i = 0;
	while (a < lenmax)
		dest[i++] = (char)s1[a++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}
