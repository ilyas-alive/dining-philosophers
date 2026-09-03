NAME = codexion

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread 

SRCS = src/main.c \
       src/parse.c \
       src/queues.c \
       src/init_config.c \
       src/get_time.c \
       src/free.c \
       src/coder_routine.c \
       src/monitor.c \
       src/routine.c \
       src/utils.c

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
