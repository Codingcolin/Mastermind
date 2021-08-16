FLAGS = -Wall -Werror -Wextra 
NAME = my_mastermind
SRC = *.c
OBJECTS = *.o
SANITIZE = -fsanitize=address

all: $(SRC)
	gcc $(FLAGS) $(SANITIZE) $(SRC) -o my_mastermind

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
