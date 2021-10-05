PROJECT		= minishell
NAME		= minishell
NAME_BONUS	= minishell
LIBFT		= libft/libft.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
ifndef NO_SANITIZE
CFLAGS	+= -fsanitize=address
endif
ifdef DEBUG
CFLAGS	+= -g
endif

# Common
LIBS	= -L$(dir $(LIBFT)) -lft
HEADERS	= libft/libft.h
SOURCES	=

ifndef BONUS
# Not Bonus
SOURCES	+=
HEADERS	+=
CFLAGS	+=
LIBS	+=
else
# Bonus
NAME	=$(NAME_BONUS)
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
INCLUDES = $(addprefix -I,$(dir $(HEADERS)))

.PHONY: all clean fclean re debug bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "make"
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)
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
