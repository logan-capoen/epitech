##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for secured
##

SRC = 	secured.c \
		usefull_functions.c

NAME = libhashtable.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C lib/my all
	ar rcT $(NAME) $(OBJ) libmy.a

clean:
	$(MAKE) -C lib/my clean
	rm -f $(OBJ)
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	$(MAKE) -C lib/my fclean
	rm -f $(NAME)
	rm -f $(LCNAME)
	rm -f libmy.a

re:		fclean all
