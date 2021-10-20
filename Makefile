# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/06 11:47:27 by mvan-wij      #+#    #+#                  #
#    Updated: 2021/10/20 17:59:14 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

PROJECT		= minishell
NAME		= minishell
NAME_BONUS	= minishell
LIBFT		= libft/libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
DATA_FILE	= .make_data.txt
ifndef NO_SANITIZE
CFLAGS	+= -fsanitize=address
endif
ifdef DEBUG
CFLAGS	+= -g
endif

# Common
LIBS	= -L$(dir $(LIBFT)) -lft -L$(HOME)/.brew/Cellar/criterion/2.3.3/lib -lcriterion
HEADERS	= libft/libft.h include/structs.h include/utilities.h include/lex.h include/parse.h
SOURCES	= src/lexing/lex.c src/lexing/utils.c src/lexing/lex_part.c src/lexing/expand.c src/parse.c

ifdef DO_TESTS
CFLAGS	+= -DDO_TESTS=1
SOURCES += $(filter-out src/test/init.c, $(wildcard src/test/*.c)) src/test/init.c
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
INCLUDES = $(addprefix -I,$(dir $(HEADERS))) -I$(HOME)/.brew/Cellar/criterion/2.3.3/include

PRE_RULES	=
ifneq ($(shell echo "$(CFLAGS)"), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES	+= clean
endif

.PHONY: all clean fclean re debug bonus

all: $(PRE_RULES) $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "make"
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)
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
