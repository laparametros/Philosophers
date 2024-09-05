CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
NAME = philo_bonus
SRC_DIR = src
OBJ_DIR = obj
RM = rm -rf
SRC = src/control_args.c src/dead.c src/eat.c src/think.c src/free_properties.c src/philo_functions.c src/philosophers_init.c src/philo.c src/time.c src/sleep.c src/fork.c \

OBJ =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) 
	gcc $(OBJ) -lpthread -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

.PHONY: all fclean clean re
