##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for my_ls
##

SRC = 	main.c \
		my_ls.c \
		reverse.c \
		handling.c \
		handling_l_flag.c

NAME = my_ls

OBJ = $(SRC:.c=.o)

LCNAME = unit_tests

CFLAGS = -Iinclude/. -L. -lmy

LCFLAGS = --coverage -lcriterion

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
		valgrind --leak-check=full ./my_ls -l include/

unit_tests:
	gcc -o unit_tests tests/test_my_ls.c \
	-Iinclude/. -L. -lmy -lcriterion --coverage

tests_run:
	./$(LCNAME)
