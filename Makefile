CC  = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft
NAME = philosophers
DEPS = philosophers.h
SRCS = philosophers.c# parser.c
OBJS = $(SRCS:.c=.o)
LIBDIR = ./libft
LIBMAKE = $(LIBDIR)/libft.a

all: $(NAME) 

$(NAME) : $(OBJS) $(LIBMAKE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBMAKE) -o $(NAME)

$(LIBMAKE):
	make -C $(LIBDIR)

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBDIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -f  $(NAME)

re: fclean all

.PHONY: all clean fclean re
