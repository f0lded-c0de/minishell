SRC =	parsing/tokens/is_charset.c parsing/tokens/checks.c \
		parsing/tokens/tokeniser.c parsing/tokens/utils.c \
		parsing/heredocs/get_delim.c parsing/heredocs/heredocs.c \
		parsing/heredocs/utils.c \
		parsing/expand/expand.c \
		parsing/pipeline/pipeline.c parsing/pipeline/utils.c \
		exec/builtins/ft_cd.c exec/builtins/ft_echo.c \
		exec/builtins/ft_env.c exec/builtins/ft_exit.c \
		exec/builtins/ft_export.c exec/builtins/ft_export_2.c \
		exec/builtins/ft_pwd.c exec/builtins/ft_unset.c \
		exec/builtins/utils.c \
		exec/exec_pipeline/exec_bltn.c exec/exec_pipeline/exec_cmd.c \
		exec/exec_pipeline/exec_pipeline.c exec/exec_pipeline/path.c \
		exec/exec_pipeline/redirs.c exec/exec_pipeline/utils.c \
		exec/signal.c \
		core/main.c core/errors.c core/str.c

TST =	parsing/heredocs/get_delim.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Werror -Wextra -I./includes -I./libft

LDFLAGS = -L./libft

LDLIBS = -lft -lreadline

NAME = minishell

DEBUG = debug

LIBFT = libft

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	cc -v $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	make clean

$(DEBUG): $(SRC)
	make -C $(LIBFT)
	cc $(CFLAGS) -g3 $(SRC) -o $(DEBUG) $(LDFLAGS) $(LDLIBS)
	make clean

test: $(TST)
	make -C $(LIBFT)
	cc $(CFLAGS) $(TST) -o test $(LDFLAGS) $(LDLIBS)
	make clean

clean:
	rm -f */*.o
	rm -f */*/*.o
	rm -f $(LIBFT)/libft.a

fclean: clean
	rm -f $(NAME) $(DEBUG)

re: fclean all

.PHONY: all clean fclean re debug
