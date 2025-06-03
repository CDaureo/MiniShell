NAME = minishell

SRC_FILES = ./src
SRC_UTILS = $(SRC_FILES)/utils
SRC_LIBRARY = $(SRC_FILES)/library

SRC_ERRORS = $(SRC_FILES)/errors

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