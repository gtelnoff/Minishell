/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:32:46 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 04:32:48 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"


void	ft_putchar_fd(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

static int	sizemalloc(int n)
{
	unsigned int	nbis;
	int				i;

	nbis = (unsigned int)n;
	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		i++;
		nbis = n * -1;
	}
	while (nbis > 0)
	{
		nbis /= 10;
		i++;
	}
	return (i);
}

static void	swap(char *dest)
{
	char	a;
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(dest) - 1;
	if (dest[0] == '-')
		i += 1;
	while (++i < len)
	{
		a = dest[i];
		dest[i] = dest[len];
		dest[len--] = a;
	}
}

char	*ft_itoa(int n)
{
	char			*dest;
	int				i;
	unsigned int	nbis;

	nbis = (unsigned int)n;
	i = -1;
	dest = malloc(sizeof(char) * (sizemalloc(n) + 1));
	if (!dest)
		return (0);
	if (n < 0)
	{
		nbis = n * (-1);
		dest[++i] = '-';
	}
	while (nbis >= 10)
	{
		dest[++i] = (nbis % 10) + '0';
		nbis /= 10;
	}
	dest[++i] = nbis + '0';
	dest[++i] = '\0';
	swap(dest);
	return (dest);
}

char	*ft_strdup(char *source)
{
	char	*dest;
	char	*sourcebis;
	int		i;

	if (source == NULL)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(source) + 1));
	if (!dest)
		return (NULL);
	sourcebis = source;
	i = -1;
	while (source[++i])
		dest[i] = sourcebis[i];
	dest[i] = '\0';
	return (dest);
}
