NAME	= biggest

SRC	= biggest_sum.c

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -pedantic

OBJ	= $(SRC:.c=.o)

all	: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) -o $@ $<

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all

test	: $(NAME)
	@./$(NAME) 3 -1 -5 2 4 -3 6 -4 2 5 -8 3 1 -7 6 -2
# Must be 12

.PHONY: all clean fclean re test
