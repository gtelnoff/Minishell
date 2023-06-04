/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:01 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/19 18:39:19 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [exit.c]
// int	verif_letter(char *tab);
// int	loop_strdiff(int i, int j, char *s1, char *s2);
// int	ft_strdiff(char *s1, char *s2);
// int	exit_function(char **tab, t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

void	error_exit_nar(t_parse *parse, t_cmd cmd);
void	error_exit_nr(t_parse *parse, t_cmd cmd);
void	error_exit_tma(t_parse *parse, t_cmd cmd);

int	verif_letter(char *tab)
{
	int	i;

	i = 0;
	if (tab[0] == '-' || tab[0] == '+')
		i = 1;
	while (tab[i])
	{
		if (tab[i] >= '0' && tab[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	loop_strdiff(int i, int j, char *s1, char *s2)
{
	if (ft_strcmp(s2, "9223372036854775807") == 0)
		return (1);
	while (s1[i] || s2[i + j])
	{
		if (s1[i] == s2[i + j])
			i++;
		else if (s1[i] > s2[i + j])
			return (1);
		else
			return (0);
	}
	return (1);
}

int	ft_strdiff(char *s1, char *s2)
{
	int	i;
	int	j;
	int	len1;
	int	len2;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (s2[0] != '-')
	{
		len2 += 1;
		j += 1;
	}
	if (len1 > len2)
		return (1);
	if (len1 < len2)
		return (0);
	if (!loop_strdiff(i, j, s1, s2))
		return (0);
	return (1);
}

void	exit_globale(t_parse *parse)
{
	unsigned char	c;

	c = g_return_status;
	free_2d_array(parse->envp);
	free_all_struct_cmd(parse->cmd);
	ft_put_str("exit\n", 1);
	exit(c);
}

void	exit_function(char **tab, t_parse *parse, t_cmd cmd)
{
	unsigned char	c;

	if (!tab[1])
		exit_globale(parse);
	else if (!verif_letter(tab[1]))
	{
		error_exit_nar(parse, cmd);
		return ;
	}
	else if (tab[2])
	{
		error_exit_tma(parse, cmd);
		return ;
	}
	else if (!ft_strdiff("-9223372036854775808", tab[1]))
	{
		error_exit_nr(parse, cmd);
		return ;
	}
	c = ft_atoi(tab[1]);
	free_2d_array(parse->envp);
	ft_put_str("exit\n", 1);
	free_all_struct_cmd(parse->cmd);
	exit(c);
}
