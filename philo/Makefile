NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
M_SRC = philo.c \
		parser.c \
		allocate.c \
		threads.c
M_OBJS = $(M_SRC:%.c=%.o)

all :$(NAME)
$(NAME) : $(M_OBJS) philo.h
		$(CC) $(CFLAGS) $(M_OBJS) -o $@ -fsanitize=address -g

%.o : %.c philo.h
		$(CC) $(CFLAGS) -c $< -o $@
clean: 
		rm -rf $(M_OBJS)
fclean: clean
		rm -rf $(NAME)
re: fclean all
