/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils04.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:59:21 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/13 14:07:44 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [utils04.c]
// char	*ft_strdup_parsing(const char *s);
// int	strlen_stop(char *str, char c);
// int	ft_atoi(const char *nptr);
// ------------------PROTOTYPE POUR LE ".h"------------------

char	*ft_strdup_parsing(const char *s)
{
	int		i;
	char	*str;
	char	*st;

	if (!s)
		return (NULL);
	st = (char *)s;
	i = 0;
	while (st[i])
		i++;
	str = malloc(sizeof (char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (st[++i])
		str[i] = st[i];
	str[i] = '\0';
	return (str);
}

int	strlen_stop(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	final;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	neg = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if ((nptr[i] == '-' || nptr[i] == '+')
			&& (!(nptr[i + 1] >= '0' && nptr[i + 1] <= '9')))
			return (0);
		else if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	final = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		final = (final * 10) + (nptr[i] - 48);
		i++;
	}
	return (final * neg);
}
