/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:01 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/22 20:12:54 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [export_utils02.c]
// int identifier_character(char c);
// int there_is(char *str, char c, char v);
// ------------------PROTOTYPE POUR LE ".h"------------------

int	identifier_character(char c)
{
	if ((c >= 'a' && c <= 'z') \
	|| (c >= 'A' && c <= 'Z') || c == '_')
		return (TRUE);
	return (FALSE);
}

int	there_is(char *str, char c, char v)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c || (str[i] == v \
		&& str[i + 1] == c))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
