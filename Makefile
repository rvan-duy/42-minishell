PROJECT		= minishell
NAME		= minishell
NAME_BONUS	= minishell
LIBFT		= libft/libft.a

CC		= gcc
CFLAGS	= -Wall -Wextra
ifdef SANITIZE
CFLAGS	+= -g -fsanitize=address
endif
ifdef DEBUG
CFLAGS	+= -g
endif

# Common
LIBS	= -L$(dir $(LIBFT)) -lft -lreadline -L$(HOME)/.brew/Cellar/criterion/2.3.3/lib -lcriterion

HEADERS	=	libft/libft.h \
			include/structs.h \
			include/execute.h \
			include/safe.h \
			include/utilities.h \
			src/ruben_tests/tests.h

SOURCES	=	src/execute.c \
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
			src/envp/env_arr_to_list.c \
			src/envp/env_list_to_arr.c \
			src/envp/env_get_var.c \
			src/envp/env_node_add.c \
			src/envp/env_node_last.c \
			src/envp/env_node_new.c \
			src/envp/env_node_del.c \
			src/envp/env_list_len.c \
			src/envp/env_node_dup.c \
			src/ruben_tests/criterion/criterion_test_tmp.c

TMP_SOURCES = 	src/ruben_tests/criterion/criterion_tests.c

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
INCLUDES = $(addprefix -I,$(dir $(HEADERS))) -I$(HOME)/.brew/Cellar/criterion/2.3.3/include

.PHONY: all clean fclean re debug bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "make"
	$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBS) -o $(NAME)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : $(BLUE_FG)$(NAME)$(RESET_COLOR) created\n" "[$(PROJECT)]" "make"

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
