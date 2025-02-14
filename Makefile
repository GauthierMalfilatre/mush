##
## EPITECH PROJECT, 2025
## MINISHELL1
## File description:
## Makefile for minishell1
##

SRC =	src/mysh.c \
		src/cd/my_cd.c \
		src/pathfinder.c \
		src/env/find_in_env.c \
		src/env/env_to_linked_list.c \
		src/env/setenv.c \
		src/env/reverse.c \
		src/env/destroy.c \
		src/env/unsetenv.c \
		src/data/init.c \
		src/error.c \
		src/child.c

OBJ = $(SRC:.c=.o)

TESTS_FOLDER = test_bash

NAME = mysh

CFLAGS = -Wall -Wextra -g -Iinclude/

all: $(NAME)

$(NAME): $(OBJ)
	@rm -f include/my_printf.h
	@make -C lib/my > /dev/null
	@cp lib/libmy.a libmy.a
	gcc -o $(NAME) $(OBJ) -Llib/ -lmy -lc
	@echo "MAKED"

.PHONY: valgrind
valgrind:	re
	valgrind --track-origins=yes --leak-check=full ./$(NAME)

#test:
#	gcc -w -o unit_test tests/*.c --coverage -lcriterion -L. -lmy
#	./unit_test
#	make fclean > /dev/null
#	rm unit_test > /dev/null

.PHONY: tests
tests: re
	cp $(NAME) $(TESTS_FOLDER)/
	cd $(TESTS_FOLDER)
	./tester.sh
	cd ../

.PHONY: clean
clean:
	@find . -name "*~" -delete -o -name "#*#" -delete -o -name "*.out" -delete
	@find . -name "*.o" -delete -o -name "unit_tests"  -delete > /dev/null
	@find . -name "*.a" -delete -o -name "*.log" -o -name "'#*#'" -delete
	@find . -name "*.gcda" -delete -o -name "*.gcno" -delete > /dev/null
	@find . -name "unit_test" -delete > /dev/null
	@echo "CLEAN"

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)

.PHONY: code
code: fclean
	@coding-style . . > /dev/null
	@cat coding-style-reports.log
	@rm -f coding-style-reports.log
	@echo "CODING-STYLE CHECKED"

.PHONY: push
push: fclean
	@git add .
	@echo "What did you change ?" ; read COMMIT ; git commit -m "$$COMMIT"
	@git push -u origin main

re: fclean all

.PHONY: cowsay_%
cowsay_%:
	@echo " -------"
	@echo "| $(*F) |"
	@echo " -------"
	@echo "        \\   ^__^"
	@echo "         \\  (oo)\\_______"
	@echo "            (__)\\       )\\/\\"
	@echo "                ||----w |"
	@echo "                ||     ||"

.PHONY: kronk
kronk:
	@echo "Oh ouais."
