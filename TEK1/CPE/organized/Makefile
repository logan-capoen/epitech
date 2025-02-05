##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for organized
##

SRC = 	main.c \
		add.c \
		display.c \
		delete.c \
		sort.c \
		tools_functions.c

NAME = organized

OBJ = $(SRC:.c=.o)

CFLAGS = -Iinclude/. -Ilibshell/. -L. -lmy -Llibshell/. -lshell

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C lib/my all
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

libmy.a:
	$(MAKE) -C lib/my

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

debug:
		gcc -o $(NAME) $(SRC) $(CFLAGS) -g
		valgrind --leak-check=full ./organized -l include/
