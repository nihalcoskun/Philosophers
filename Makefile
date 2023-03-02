NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
SRCS	= begin.c check.c init.c life.c main.c thread.c utils.c
OBJS	= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean	:
		rm -rf $(OBJS)

fclean	:	clean
		rm -rf $(NAME)
re		: fclean all

.PHONY	: all clean fclean re