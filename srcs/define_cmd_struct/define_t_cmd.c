/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_t_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:25:16 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/11/10 17:25:17 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	define_all_cmd_null(t_cmd *cmd, int nb_of_cmd);
void	define_all_cmd_params(t_parse *parse, char **array);
void	define_all_no_parse_cmd(t_parse *parse, int nb_of_cmd);
void	define_all_redirection(t_parse *parse, int nb_of_cmd);
void	delete_all_quote(t_parse *parse, int nb_of_cmd);
void	define_all_path(t_parse *parse, int nb_of_cmd);
char	*ft_itoa(int n);
char	**array_dup(char **array);
int		get_len_newstr(char **array);
char	**delete_null_byte(char **array);
char	*make_new_str_with_dollar_value(char *str, char *return_value,
			int index, int len);
char	*change_dollar(char *str, char *return_value);
void	change_dollar_value_in_cmd(t_cmd *cmd, int index);
void	change_all_dollar_return_value(t_cmd *cmd, int nb_of_cmd);

int	define_t_cmd(t_parse *parse, char **array)
{
	int	nb_of_cmd;

	nb_of_cmd = give_nb_of_cmd(array);
	if (have_parse_error(array))
	{
		free_2d_array(array);
		return (-1);
	}
	array = delete_null_byte(array);
	parse->cmd = malloc(sizeof(t_cmd) * (give_nb_of_cmd(array) + 1));
	define_all_cmd_null(parse->cmd, nb_of_cmd);
	define_all_cmd_params(parse, array);
	change_all_dollar_return_value(parse->cmd, nb_of_cmd);
	define_all_no_parse_cmd(parse, nb_of_cmd);
	define_all_redirection(parse, nb_of_cmd);
	delete_all_quote(parse, nb_of_cmd);
	define_all_path(parse, nb_of_cmd);
	free_2d_array(array);
	return (nb_of_cmd);
}

int	get_len_newstr(char **array)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (array[i] != NULL)
	{
		if (array[i][0] != '\0')
			x++;
		i++;
	}
	if ((x - i) == 0)
		return (-1);
	return (x);
}

char	**array_dup(char **array)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = malloc(sizeof(char *) * (get_len_2d_array(array) + 1));
	while (array[i] != NULL)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	free_2d_array(array);
	new_array[i] = NULL;
	return (new_array);
}

////////////////////////////////
//////
//////	Description: define_all_cmd_null permet de initialiser
//////					toutes les valeurs; des structs t_cmd a NULL.
//////
//////	Valeur de retour: NONE.
//////
////////////////////////////////
void	define_all_cmd_null(t_cmd *cmd, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		cmd[i].fd.heredoc[0] = 0;
		cmd[i].fd.heredoc[1] = 0;
		cmd[i].fd.fd_in = 0;
		cmd[i].fd.fd_out = 0;
		cmd[i].possible_excution = 0;
		cmd[i].index_error_redirection = -1;
		cmd[i].cmd_path = NULL;
		cmd[i].no_parse_cmd = NULL;
		cmd[i].cmd_params = NULL;
		cmd[i].all_redirection = NULL;
		i++;
	}
}

////////////////////////////////
//////
//////	Description: give_nb_of_cmd, permet de connaitre le nombre de;
//////					commande a excuter.
//////
//////	Valeur de retour: le nombre de cmd de la ligne entree.
//////
////////////////////////////////
int	give_nb_of_cmd(char **array)
{
	int	i;
	int	nb_of_cmd;

	i = 0;
	nb_of_cmd = 1;
	while (array[i] != NULL)
	{
		if (array[i][0] == '|' && array[i][1] == '\0')
			nb_of_cmd++;
		i++;
	}
	return (nb_of_cmd);
}
