/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:01 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/22 20:08:44 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [export_utils.c]
// int	verif_var_character(char *tab);
// char	*var_without_no_more(char *tab);
// int is_this_character(char *str, char c);
// int	check_other_identifier(char *str, int i):
// int	check_valid_identifier(char *str);
// ------------------PROTOTYPE POUR LE ".h"------------------

int	verif_var_character(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i + 1] && tab[i] == '+' && tab[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*var_without_no_more(char *tab)
{
	int		i;
	int		j;
	char	*clean_tab;

	i = 0;
	j = 0;
	clean_tab = malloc(sizeof(char) * ft_strlen(tab));
	while (tab[i])
	{
		if (tab[i] != '+')
			clean_tab[j++] = tab[i];
		i++;
	}
	clean_tab[j] = '\0';
	return (clean_tab);
}

int	is_this_character(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	check_other_identifier(char *str, int i)
{
	int	temp;

	temp = i;
	i = identifier_character(str[0]);
	if (i == temp)
		return (FALSE);
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_')
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

int	check_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=' && !str[i + 1])
		return (FALSE);
	if (is_this_character(str, '='))
	{
		i = identifier_character(str[0]);
		if (i == 0)
			return (FALSE);
		while (str[i] != '=')
		{
			if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| (str[i] == '+' && str[i + 1] == '=') || str[i] == '_')
				i++;
			else
				return (FALSE);
		}
	}
	else if (!check_other_identifier(str, i))
		return (FALSE);
	return (TRUE);
}
