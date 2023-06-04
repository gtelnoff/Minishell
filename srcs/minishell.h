/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:13:06 by gtelnoff          #+#    #+#             */
/*   Updated: 2022/12/22 20:15:55 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "cmd.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>

# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7
# define TRUE 1
# define FALSE 0

typedef struct s_index
{
	int			i;
	int			j;
	int			len;
}				t_index;

typedef struct s_parse
{
	int			fds1[2];
	int			fds2[2];
	t_cmd		*cmd;
	t_index		index;
	char		**env;
	char		**envp;
	char		*print_path;
	char		*var;
	char		*clean_var;
	char		*path;
	char		*line;
	int			cmpt_line;
	int			len_envp;
	char		**fill_tab;
}				t_parse;

extern int		g_return_status;
void			free_path(t_cmd *cmd, int index, char *cmd_buf,
					char **all_path);
char			**get_all_path(char **env, char **all_path, int index);
void			free_path_env(t_cmd *cmd, char **all_path, int x);
char			*ft_delete_path_envp(char **env, int index);
void			free_2d_array(char **array);
void			catch_signal_main(int sig);
char			*ft_strjoin_no_space(char *s1, char *s2, int index);
int				get_len_2d_array(char **array);
char			*make_1d_array(char **array);
char			*ft_strtrim(char *s1, char *set);
size_t			ft_strlen(const char *s);
int				have_parse_error(char **array);
void			*ft_calloc(size_t elementCount, size_t elementSize);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				countab(char const *s, char c);
unsigned int	countchar(char const *s, char c, unsigned int x);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char *s1, char *s2, int x);
int				specific_redirection(t_cmd *cmd, int i, int index,
					char **redirection_out);
int				define_t_cmd(t_parse *parse, char **array);
void			define_all_redirection(t_parse *parse, int nb_of_cmd);
void			excute_cmds(t_parse *parse);
void			ft_put_str(char *str, int fd);
void			print_t_cmd(t_cmd *cmd, int nb_of_cmd);
char			*ft_strdup(char *source);
int				get_nb_of_cmd(t_cmd *cmd);
int				is_redirection_in(char *redirection);
int				is_simple_redirection_in(char *redirection);
int				is_redirection_out(char *redirection);
void			catch_signal_heredoc(int sig);
void			print_2d_array(char **array);
int				is_builtins(char *cmd_path);
void			make_here_doc(t_cmd *cmd, char **redirection, int index);
int				is_here_doc(char *str);
void			ft_putchar_fd(int fd, char *str);
void			check_here_doc_in(t_cmd *cmd, char **redirection);
int				make_dup2_out(t_parse *parse, t_cmd cmd, int index,
					int nb_of_cmd);
int				make_dup2_in(t_parse *parse, t_cmd cmd, int index);
void			close_all_child_fd(t_parse *parse, int nb_of_cmd, int index);
void			open_all_redirection(t_cmd *cmd);
void			open_all_here_doc(t_cmd *cmd, int nb_of_cmd);
void			open_all_simple_redirection_in(t_cmd *cmd, int nb_of_cmd);
void			open_all_redirection_out(t_cmd *cmd, int nb_of_cmd);
void			wait_pid_heredoc(pid_t pid);
int				get_all_pid(t_cmd *cmd);
void			child(t_parse *parse, pid_t pid, int index, int *all_pid);
void			open_pipe(t_parse *parse, int index);
void			close_pipe(t_parse *parse, int index);
void			close_all_main_fd(t_parse *parse);
void			exit_heredoc(t_cmd *cmd);
char			*ft_itoa(int n);
void			print_all_error_cmd(t_cmd *cmd);
void			here_doc_child(t_cmd *cmd, char **redirection, int index,
					int i);
void			get_return_status(int last_cmd_status, int return_status);
int				check_permission_outfile(t_cmd *cmd, char *file_name, int fd,
					int index);
void			catch_signal(int sig);
void			make_all_wait_pid(t_parse *parse, pid_t *all_pid);
int				is_builtins(char *cmd_path);
int				check_builtins(t_parse *parse);
void			excute_builtins(t_parse *parse, t_cmd cmd, int builtins_numbers,
					int *fds_one_zero);
int				check_builtins_child(t_parse *parse, int is_child, int index, \
					int *all_pid);
void			builtins_cd(t_parse *parse, t_cmd cmd, char **cmd_params);
void			builtins_pwd(t_parse *parse, t_cmd cmd);
void			unset(char **tab, t_parse *parse, t_cmd cmd);
void			builtins_env(t_parse *parse, t_cmd cmd, char **cmd_params);
void			change_return_value(t_cmd *cmd, int return_status,
					int index_cmd);

//<------->{file}->[echo.c]
char			*ft_strjoin_free(char *s1, char *s2, int index);
char			*double_tab_to_simple(char **array, int n);
int				verif_first_argument(char *str);
void			echo(t_parse *parse, t_cmd cmd, char **tab);

//<------->{file}->[error.c]
void			ft_error_exit(char *str, int code);
void			ft_error_export(int code);
void			ft_error_parse(char *str, int code);
void			ft_error(char *str, int code, int free, t_parse *parse);

//<------->{file}->[exit.c]
int				verif_letter(char *tab);
int				loop_strdiff(int i, int j, char *s1, char *s2);
int				ft_strdiff(char *s1, char *s2);
void			exit_function(char **tab, t_parse *parse, t_cmd cmd);

//<------->{file}->[export_utils.c]
int				verif_var_character(char *tab);
char			*var_without_no_more(char *tab);
int				is_this_character(char *str, char c);
int				check_other_identifier(char *str, int i);
int				check_valid_identifier(char *str);

//<------->{file}->[export.c]
int				check_same_var(char *tab, t_parse *parse);
char			*add_arg_to_var(int index, char *tab, t_parse *parse);
int				loop_export(char **tab, int i, int j, t_parse *parse);
void			export(char **tab, t_parse *parse, t_cmd cmd);

//<------->{file}->[fill_tab_arg_utils.c]
int				cmpt_words(char *s);
int				check_character(int i, int len, char *str, int nb);
void			condition_fill_tab(t_parse *parse);

//<------->{file}->[fill_tab_arg.c]
void			fill_tab_arg(t_parse *parse);
void			find_and_split(t_parse *parse);
void			find_quote(char c, t_parse *parse);
void			split_special_character(int len, t_parse *parse);
int				find_quote_next_to_char(char c, t_parse *parse);

//<------->{file} [free_exit.c]
void			ft_free(t_parse *parse, int check);
void			ft_exit(unsigned char c, t_parse *parse);

//<------->{file} [line_parser_utils01.c]
int				check_quote_in_quote(char *str, char c, int i);
int				peer_quote(char *str);
int				check_quote_charactere(char *str, char c, int i);
int				check_quoted_string(char *str);
int				check_unquoted_string(char *str);

//<------->{file} [line_parser_utils02.c]
int				condition_clean_rl(char *str, char *clean, char c, int i);
char			*clean_read_line(int i, char c, char *str);
int				strnlen_stop(char *str, char c, int size);
char			*clean_line(int i, char c, char *str);

//<------->{file} [line_parser_utils03.c]
char			*condition_special_check(char *str, int i, t_parse *parse);
char			*check_quotes(char *str, int i, t_parse *parse);
char			*second_parser(char *str, t_parse *parse);
int				check_dollar_character(char *str);
int				check_quote_and_char_next_to(int i, char c, char *str);

//<------->{file}->[line_parser.c]
int				verif_inside_character(char *str, char c, int i);
int				verif_inside_quote(char *str, char c, int i);
char			*special_check(char *str, t_parse *parse);
int				first_parser(t_parse *parse);

//<------->{file}->[parsing.c]
void			init_struct_value(t_parse *parse);
void			malloc_envp(char **env, t_parse *parse);
char			**parsing(t_parse *parse);

//<------->{file}->[print_env_utils01.c]
int				ft_tablen(char **tab);
int				check_quote(int i, char c, t_parse *parse);
char			*clean_path(char *path, t_parse *parse);
int				ft_str_path(char *big, char *little);
int				chech_correct_path_arg(int i, char *str);

// {file} [print_env_utils02.c]
char			*delete_dollar(char *str, int index);
int				many_dollar_loop(int index_i, t_parse *parse);
void			many_dollar(int index_i, int index_j, t_parse *parse);
int				there_is_character(char *str, int index, t_parse *parse);

//<------->{file}->[print_env.c]
void			change_tab_path(int i, int temp, t_parse *parse);
int				loop_find_path(char *no_dollar, t_parse *parse);
int				find_path(int index_i, int index_j, t_parse *parse);
int				loop_search_path(int i, int j, int temp, t_parse *parse);
void			search_path(t_parse *parse);

//<------->{file}->[print_export.c]
char			*add_quote2(char *tmp, int count, int i, int j);
char			*add_quote(char *str);
void			add_argument_into_export(t_parse *parse);
void			sort_loop(t_parse *parse);
void			print_export(t_parse *parse);

//<------->{file}->[utils01.c]
char			**ft_split_parsing(char const *s, char c);
char			*ft_substr_parsing(char const *s, unsigned int start,
					size_t len);

//<------->{file}->[utils02.c]
int				ft_strlen_parsing(const char *s);
char			*ft_strnstr(const char *big, const char *little, size_t len);
void			*ft_calloc_parsing(size_t nmemb, size_t size);
void			ft_bzero(void *s, size_t n);
int				ft_strcmp(char *s1, char *s2);

//<------->{file}->[utils03.c]
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strcat(char *dst, const char *src);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*ft_strjoin_parsing(char const *s1, char const *s2);

//<------->{file}->[utils04.c]
char			*ft_strdup_parsing(const char *s);
int				strlen_stop(char *str, char c);
int				ft_atoi(const char *nptr);
int				ft_strncmp(char *first, char *second, int length);
int				identifier_character(char c);
int				there_is(char *str, char c, char v);

#endif
