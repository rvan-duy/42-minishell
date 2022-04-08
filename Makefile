# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/06 11:47:27 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/04/08 13:36:17 by rvan-duy      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

PROJECT			= minishell
NAME			= minishell
LIBFT			= libft/libft.a
BREW_DIR		= $(shell brew --prefix)
LIBREADLINE		= $(BREW_DIR)/opt/readline/lib/libreadline
LIBCRITERION	= $(BREW_DIR)/opt/criterion/lib/libcriterion

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
DATA_FILE	= .make_data.txt
ifdef SANITIZE
CFLAGS	+= -fsanitize=address -g3
endif
ifdef DEBUG
CFLAGS	+= -g3
endif

# Common
LIBS = $(LIBFT) $(LIBREADLINE) # $(LIBCRITERION)

HEADERS	=					\
	libft/libft.h			\
	include/builtins.h		\
	include/cmds.h			\
	include/debug.h			\
	include/envp.h			\
	include/error.h			\
	include/execute.h		\
	include/parse.h			\
	include/safe.h			\
	include/signals.h		\
	include/structs.h		\
	include/lex.h

HEADER_DIRS =							\
	$(BREW_DIR)/opt/readline/include	\
	# $(BREW_DIR)/opt/criterion/include

SOURCES	=									\
	src/execute_line.c						\
	src/safe/safe_chdir.c 					\
	src/safe/safe_check_access.c 			\
	src/safe/safe_close.c 					\
	src/safe/safe_create_pipe.c 			\
	src/safe/safe_dup2.c 					\
	src/safe/safe_fork.c 					\
	src/safe/safe_open.c 					\
	src/safe/safe_wait.c					\
	src/builtins/builtin_cd.c 				\
	src/builtins/builtin_check_and_exec.c	\
	src/builtins/builtin_echo.c 			\
	src/builtins/builtin_env.c 				\
	src/builtins/builtin_exit.c 			\
	src/builtins/builtin_export.c 			\
	src/builtins/builtin_export_list.c		\
	src/builtins/builtin_pwd.c 				\
	src/builtins/builtin_unset.c 			\
	src/envp/env_arr_to_list.c 				\
	src/envp/env_get_var.c 					\
	src/envp/env_node_add.c 				\
	src/envp/env_node_last.c 				\
	src/envp/env_node_new.c 				\
	src/envp/env_node_del.c 				\
	src/envp/env_node_dup.c 				\
	src/envp/env_list_len.c 				\
	src/envp/env_list_dup.c 				\
	src/envp/env_list_free.c 				\
	src/envp/env_list_to_arr.c 				\
	src/lex/0a_utils.c						\
	src/lex/0b_utils.c						\
	src/lex/1_get_tokens.c					\
	src/lex/1a_token_completion.c			\
	src/lex/2_validity.c					\
	src/lex/3_expand_vars.c					\
	src/lex/4_redirect_names.c				\
	src/lex/5_fix_unquoted.c				\
	src/lex/6_join_words.c					\
	src/lex/7_remove_whitespace.c			\
	src/lex/8_create_nodes.c				\
	src/parse_line.c						\
	src/signals/signal_handlers.c			\
	src/cmds/cmd_get_valid_path.c			\
	src/cmds/cmd_create_execve_array.c		\
	src/cmds/cmd_exec_single_file.c			\
	src/cmds/cmd_exec_multiple_files.c		\
	src/cmds/cmd_io_redirections.c			\
	src/cmds/cmd_expand_heredoc.c			\
	src/errors/error_is_dir.c				\
	src/debug/debug_print_nodes.c

TMP_SOURCES = src/ruben_tests/criterion/criterion_tests.c src/ruben_tests/criterion/criterion_test_tmp.c $(filter-out src/test/init.c, $(wildcard src/test/*.c)) src/test/init.c

ifndef DO_TESTS
SOURCES += 	src/main.c
endif

include $(dir $(LIBFT))/colours.mk
RULE_SPACING	= 6
PROJECT_SPACING	= 11

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%, $(SOURCES:c=o))
INCLUDES = $(sort $(addprefix -I,$(dir $(HEADERS))) $(addprefix -I,$(HEADER_DIRS)))
LIB_FLAGS = $(sort $(addprefix -L,$(dir $(LIBS)))) $(sort $(addprefix -l,$(patsubst lib%,%,$(basename $(notdir $(LIBS))))))

PRE_RULES	=
ifneq ($(shell echo "$(CFLAGS)"), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES	+= fclean
endif

.PHONY: all clean fclean re debug bonus

all: $(PRE_RULES) $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "make"
	$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIB_FLAGS) -o $(NAME)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : $(BLUE_FG)$(NAME)$(RESET_COLOR) created\n" "[$(PROJECT)]" "make"
	@echo "$(CFLAGS)" > $(DATA_FILE)

bonus:
	@$(MAKE) BONUS=1

debug:
	@$(MAKE) DEBUG=1

$(LIBFT): $(addprefix $(dir $(LIBFT)),$(shell $(MAKE) -s -C $(dir $(LIBFT)) sources))
ifdef DEBUG
	@$(MAKE) SILENT=1 -C $(dir $(LIBFT)) debug
else
	@$(MAKE) SILENT=1 -C $(dir $(LIBFT))
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "make"
	@printf "$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@$(CLEAR_REST_OF_LINE)\r"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "$@"
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean: clean
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "$@"
	rm -f $(NAME)
	@$(MAKE) -C $(dir $(LIBFT)) fclean

re: fclean all
