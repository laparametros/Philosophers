
NAME = philo

CFILES = main.c aux.c philostuffer.c time.c simulation.c

OFILES = $(CFILES:.c=.o)

CFLAGS = -c -Wall -Werror -Wextra

all: $(NAME)

$(OFILES): $(CFILES)
	cc $(CFLAGS) $^

$(NAME): $(OFILES)
	cc -o $(NAME) $(OFILES)

clean:
	-rm -f $(OFILES)

fclean: clean
	-rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
