NAME = minishell

SRC_UTILS = ./utils

SRC_ERRORS = ./errors
# Include the main source directory wildcard makes it easier to add new source files
# without modifying the Makefile and the wildcard function to include all,
# .c files in the utils and errors directories.
SRC = ./src/main.c $(wildcard $(SRC_UTILS)/*.c) $(wildcard $(SRC_ERRORS)/*.c)
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re