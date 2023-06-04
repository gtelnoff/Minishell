/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:02:53 by luserbu           #+#    #+#             */
/*   Updated: 2022/12/13 14:52:06 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ------------------PROTOTYPE POUR LE ".h"------------------
// {file} [free_exit.c]
// void    ft_free(t_parse *parse, int check);
// void    ft_exit(unsigned char c, t_parse *parse);
// ------------------PROTOTYPE POUR LE ".h"------------------

void	ft_free(t_parse *parse, int check)
{
	int	i;

	i = 0;
	if (check == TRUE)
	{
		while (parse->fill_tab[i])
		{
			printf("%s\n", parse->fill_tab[i]);
			free(parse->fill_tab[i]);
			i++;
		}
		free(parse->fill_tab);
	}
	free(parse->line);
}

void	ft_exit(unsigned char c, t_parse *parse)
{
	free_2d_array(parse->envp);
	free_all_struct_cmd(parse->cmd);
	exit(c);
}
