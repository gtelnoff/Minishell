SRCS	= srcs/builtins/builtins_utils.c srcs/builtins/cd/cd.c srcs/builtins/echo/echo.c srcs/builtins/env/env.c srcs/builtins/exit/exit.c srcs/builtins/exit/exit_error.c srcs/builtins/exit/free_exit.c srcs/builtins/export/export.c srcs/builtins/export/export_error.c srcs/builtins/export/export_utils01.c srcs/builtins/export/export_utils02.c srcs/builtins/export/print_export.c srcs/builtins/pwd/pwd.c srcs/builtins/unset/unset.c srcs/builtins/unset/unset_utils.c srcs/define_cmd_struct/define_all_cmd_params.c srcs/define_cmd_struct/define_all_no_parse_cmd.c srcs/define_cmd_struct/define_all_path.c srcs/define_cmd_struct/define_all_redirection.c srcs/define_cmd_struct/define_t_cmd.c srcs/define_cmd_struct/delete_all_quote.c srcs/define_cmd_struct/parse_error.c srcs/define_cmd_struct/path.c srcs/define_cmd_struct/utils/dollar_value.c srcs/define_cmd_struct/utils/path_utils.c srcs/excution/check_builtins.c srcs/excution/child.c srcs/excution/close_child_fd.c srcs/excution/close_main_fd.c srcs/excution/excute_cmds.c srcs/excution/make_heredoc.c srcs/excution/open_heredoc.c srcs/excution/return_status.c srcs/excution/utils/check_cmd_permission.c srcs/excution/utils/check_infile_permission.c srcs/excution/utils/dup2.c srcs/excution/utils/is_redirection.c srcs/excution/utils/open_redirection.c srcs/excution/utils/pid.c srcs/excution/utils/signal.c srcs/main.c srcs/main_function.c srcs/parsing/error.c srcs/parsing/fill_tab_arg.c srcs/parsing/fill_tab_arg_utils.c srcs/parsing/line_parser.c srcs/parsing/line_parser_utils01.c srcs/parsing/line_parser_utils02.c srcs/parsing/line_parser_utils03.c srcs/parsing/parsing.c srcs/parsing/print_env.c srcs/parsing/print_env_utils01.c srcs/parsing/print_env_utils02.c srcs/parsing/utils01.c srcs/parsing/utils02.c srcs/parsing/utils03.c srcs/parsing/utils04.c srcs/utils/free_struct_cmd.c srcs/utils/ft_strjoin_no_space.c srcs/utils/split.c srcs/utils/utils_one.c srcs/utils/utils_three.c srcs/utils/utils_two.c

OBJS	= $(SRCS:.c=.o)
NAME 	= minishell
CC	= clang -g -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(OBJS) -o $(NAME) -lreadline
		echo "It's good !"

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
