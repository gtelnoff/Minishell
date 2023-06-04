/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 03:50:52 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 03:50:53 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int	is_redirection_out(char *redirection)
{
	if (redirection[0] == '>' && redirection[1] == '\0')
		return (1);
	else if (ft_strlen(redirection) == 2 && redirection[1] == '>')
		return (1);
	return (0);
}

int	is_redirection_in(char *redirection)
{
	if (redirection[0] == '<' && redirection[1] == '\0')
		return (1);
	else if (ft_strlen(redirection) == 2 && redirection[1] == '<')
		return (1);
	return (0);
}

int	is_simple_redirection_in(char *redirection)
{
	if (redirection[0] == '<' && redirection[1] == '\0')
		return (1);
	return (0);
}
