/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:13:06 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/09/12 16:13:08 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef struct s_fd
{
	int			heredoc[2];
	int			fd_out;
	int			fd_in;
}				t_fd;

typedef struct s_cmd
{
	int				possible_excution;
	int				index_error_redirection;
	char			*no_parse_cmd;
	char			*cmd_path;
	char			**cmd_params;
	char			**all_redirection;
	struct s_fd		fd;
	struct s_parse	*parse;

}				t_cmd;

int				give_nb_of_cmd(char **array);
char			**get_redirection_in(t_cmd *cmd, char **array, int x);
char			**get_redirection_out(t_cmd *cmd, char **array, int x);
char			**new_2d_array(char **array, int ignore);
void			define_cmd_path(t_cmd *cmd, int nb_of_cmd);
int				check_path(t_cmd *cmd, char **env, int x);
void			free_all_struct_cmd(t_cmd *cmd);

#endif
