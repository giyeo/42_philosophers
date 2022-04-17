NAME := philo
SRC :=	circle.c main.c \
		handle_errors.c utils.c \
		lifecycle.c handle_table.c

OBJS := $(SRC:.c=.o)

FLAG := -fsanitize=address

CFLAG := #-Wall -Wextra -Werror

all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME) $(CFLAG) $(FLAG) -lpthread

%.o: %.c
	gcc $(CFLAG) -c $< -o $@

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all