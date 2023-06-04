/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_arg_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:44:45 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/12 22:45:24 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [fill_tab_arg_utils.c]
// int	ft_words(char *s);
// int	check_character(int i, int len, char * str, int nb);
// void	condition_fill_tab(t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

int	cmpt_words(char *s)
/*	Found aproximate the number of words	*/
{
	int		i;
	int		cmpt;
	char	c;

	c = ' ';
	i = 0;
	if (s[i] == c || s[i] == 0)
		cmpt = 0;
	else
		cmpt = 1;
	while (s[i])
	{
		if ((s[i] == c || s[i] == '\"' || s[i] == '\'' \
		|| s[i] == '|' || s[i] == '<' || s[i] == '>') \
		&& s[i + 1] != c && s[i + 1] != 0)
			cmpt++;
		i++;
	}
	return (cmpt + 1);
}

int	check_character(int i, int len, char *str, int nb)
/*	Check character about value of nb	*/
{
	if (nb == 1)
		if (str[i + len] != ' ' && str[i + len])
			return (TRUE);
	if (nb == 3)
		if ((str[i + len] == '>' && str[i + len + 1] == '>') \
		|| (str[i + len] == '<' && str[i + len + 1] == '<'))
			return (TRUE);
	if (nb == 2)
		if (str[i + len] == '|' || str[i + len] == '>' \
		|| str[i + len] == '<')
			return (TRUE);
	return (FALSE);
}

void	condition_fill_tab(t_parse *parse)
{
	if (parse->line[parse->index.i] == '\"')
		find_quote('\"', parse);
	if (parse->line[parse->index.i] == '\'')
		find_quote('\'', parse);
	find_and_split(parse);
	if (parse->index.len > 0)
	{
		parse->fill_tab[parse->index.j] = \
		ft_substr_parsing((const char *)parse->line, \
		parse->index.i, parse->index.len);
		parse->index.j++;
	}
}
