NAME = minishell

SRC_FILES = ./src
SRC_UTILS = $(SRC_FILES)/utils
SRC_LIBRARY = $(SRC_FILES)/library
SRC_ERRORS = $(SRC_FILES)/errors
SRC_PARSING = $(SRC_FILES)/parsing
SRC_PIPE = $(SRC_FILES)/pipe

SRC = $(wildcard $(SRC_FILES)/*.c) $(wildcard $(SRC_UTILS)/*.c) $(wildcard $(SRC_ERRORS)/*.c) \
$(wildcard $(SRC_LIBRARY)/*.c) $(wildcard $(SRC_PARSING)/*.c) $(wildcard $(SRC_PIPE)/*.c)
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

all: libft/libft.a library/liblibrary.a $(NAME)

libft/libft.a:
	$(MAKE) -C src/library

library/liblibrary.a:
	$(MAKE) -C src/library

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C src/library clean
	$(MAKE) -C src/library clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C src/library fclean
	$(MAKE) -C src/library fclean

re: fclean all

.PHONY: all clean fclean re