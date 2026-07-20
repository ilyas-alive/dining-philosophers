NAME = a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c parse.c queues.c init_config.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME) 5 800 200 200 200 3 100 edf

# -g -fsanitize=address
