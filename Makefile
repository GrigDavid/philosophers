CC  = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread
NAME = philo
DEPS = philo.h Makefile
SRCS = aristotle.c check_death.c  ft_usleep.c parser.c philo.c print_message.c timedif.c
OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f  $(NAME)

re: fclean all

.PHONY: all clean fclean re
