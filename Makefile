NAME = minishell

SRC_FILES = ./src
SRC_UTILS = $(SRC_FILES)/utils
SRC_LIBRARY = $(SRC_FILES)/library

SRC_ERRORS = $(SRC_FILES)/errors
# Include the main source directory wildcard makes it easier to add new source files
# without modifying the Makefile and the wildcard function to include all,
# .c files in the utils and errors directories.
SRC = $(wildcard $(SRC_FILES)/*.c) $(wildcard $(SRC_UTILS)/*.c) $(wildcard $(SRC_ERRORS)/*.c) \
$(wildcard $(SRC_LIBRARY)/*.c)
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