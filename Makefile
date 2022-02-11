# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/06 11:47:27 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/02/11 13:37:15 by rvan-duy      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

PROJECT		= minishell
NAME		= minishell
NAME_BONUS	= minishell
LIBFT		= libft/libft.a

LDFLAGS += "-L$(HOME)/.brew/opt/readline/lib"

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
DATA_FILE	= .make_data.txt
ifdef SANITIZE
CFLAGS	+= -fsanitize=address
endif
ifdef DEBUG
CFLAGS	+= -g
endif

# Common
LIBS	=	-L$(dir $(LIBFT)) -lft \
			-L$(HOME)/.brew/opt/criterion/lib \
			-lcriterion \
			-lreadline

HEADERS	=	libft/libft.h \
			include/builtins.h \
			include/structs.h \
			include/execute.h \
			include/safe.h \
			include/utilities.h \
			include/lex.h \
			include/parse.h \
			include/signals.h \
			include/envp.h \
			include/cmds.h \
			include/debug.h

SOURCES	=	src/execute.c \
			src/lexing/lex.c \
			src/lexing/utils.c \
			src/lexing/lex_part.c \
			src/lexing/expand.c \
			src/parse.c	\
			src/safe/safe_chdir.c \
			src/safe/safe_check_access.c \
			src/safe/safe_close.c \
			src/safe/safe_create_pipe.c \
			src/safe/safe_dup2.c \
			src/safe/safe_fork.c \
			src/safe/safe_open.c \
			src/utils_2.c \
			src/builtins/builtin_echo.c \
			src/builtins/builtin_cd.c \
			src/builtins/builtin_pwd.c \
			src/builtins/builtin_export.c \
			src/builtins/builtin_unset.c \
			src/builtins/builtin_env.c \
			src/builtins/builtin_exit.c \
			src/envp/env_arr_to_list.c \
			src/envp/env_list_to_arr.c \
			src/envp/env_get_var.c \
			src/envp/env_node_add.c \
			src/envp/env_node_last.c \
			src/envp/env_node_new.c \
			src/envp/env_node_del.c \
			src/envp/env_list_len.c \
			src/envp/env_node_dup.c \
			src/envp/env_list_dup.c \
			src/envp/env_list_free.c \
			src/signals/signal_handler.c \
			src/cmds/cmd_get_absolute_path.c \
			src/cmds/cmd_create_execve_array.c \
			src/cmds/cmd_exec_file.c \
			src/cmds/cmd_redirect_stdin.c \
			src/debug/debug_print_nodes.c \
			src/ruben_tests/criterion/criterion_test_tmp.c

ifndef DO_TESTS
SOURCES += 	src/main.c
endif

ifndef BONUS
# Not Bonus
SOURCES	+=
HEADERS	+=
CFLAGS	+=
LIBS	+=
else
# Bonus
NAME	= $(NAME_BONUS)
SOURCES	+=
HEADERS	+=
CFLAGS	+=
LIBS	+=
endif

include $(dir $(LIBFT))/colours.mk
RULE_SPACING	= 6
PROJECT_SPACING	= 11

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%, $(SOURCES:c=o))
INCLUDES = $(addprefix -I,$(dir $(HEADERS))) -I$(HOME)/.brew/opt/criterion/include -I$(HOME)/.brew/opt/readline/include

PRE_RULES	=
ifneq ($(shell echo "$(CFLAGS)"), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES	+= clean
endif

.PHONY: all clean fclean re debug bonus

all: $(PRE_RULES) $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "make"
	$(CC) $(CFLAGS) $(OBJECTS) $(HOME)/.brew/opt/readline/lib/libreadline.dylib $(INCLUDES) $(LIBS) -o $(NAME)
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
