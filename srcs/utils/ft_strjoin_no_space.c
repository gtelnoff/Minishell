/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_no_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:17:57 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/19 18:47:47 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_no_space(char *s1, char *s2, int index)
{
	char	*s1bis;
	char	*s2bis;
	char	*dest;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s1bis = s1;
	s2bis = s2;
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = -1;
	while (s1bis[++i])
		dest[i] = s1bis[i];
	while (s2bis[++j])
		dest[i + j] = s2bis[j];
	dest[i + j] = '\0';
	if (index > 0)
		free(s2);
	return (dest);
}
