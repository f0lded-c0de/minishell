NAME = test_cd
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I../../../libft
LDFLAGS = -L../../../libft -lft

SRCS = test_cd.c ft_cd.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re