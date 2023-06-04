/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:34:26 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 04:34:27 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int		get_fdin(t_parse *parse, t_cmd cmd, int index);
int		get_fdout(t_parse *parse, t_cmd cmd, int index);

int	make_dup2_in(t_parse *parse, t_cmd cmd, int index)
{
	int	fdin;

	fdin = 0;
	fdin = get_fdin(parse, cmd, index);
	if (fdin != 0)
		dup2(fdin, 0);
	return (0);
}

int	make_dup2_out(t_parse *parse, t_cmd cmd, int index, int nb_of_cmd)
{
	int	fdout;

	fdout = get_fdout(parse, cmd, index);
	if (index == nb_of_cmd - 1 && cmd.fd.fd_out == 0)
		return (-1);
	if (fdout != 1)
		dup2(fdout, 1);
	return (0);
}
