SRC =	parsing/tokenisation/is_charset.c parsing/tokenisation/test.c \
		parsing/tokenisation/tokenisation.c parsing/tokenisation/tokens.c \
		utils/errors.c utils/str.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Werror -Wextra -I./includes -I./libft

LDFLAGS = -L./libft

LDLIBS = -lft

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

clean:
	rm -f */*.o
	rm -f $(LIBFT)/libft.a

fclean: clean
	rm -f $(NAME) $(DEBUG)

re: fclean all

.PHONY: all clean fclean re debug
