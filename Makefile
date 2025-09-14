CC  = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread
NAME = philo
DEPS = philo.h
SRCS = aristotle.c check_death.c  ft_usleep.c parser.c philo.c print_message.c timedif.c
OBJS_LOC = objs
OBJS = $(SRCS:%.c=$(OBJS_LOC)/%.o)

all: $(NAME) 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_LOC):
	mkdir -p $(OBJS_LOC)

$(OBJS_LOC)/%.o : %.c $(DEPS) | $(OBJS_LOC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_LOC)

fclean: clean
	rm -f  $(NAME)

re: fclean all

.PHONY: all clean fclean re
