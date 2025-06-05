NAME = minishell

SRC_FILES = ./src
SRC_UTILS = $(SRC_FILES)/utils
SRC_LIBRARY = $(SRC_FILES)/library
SRC_ERRORS = $(SRC_FILES)/errors
SRC_PARSING = $(SRC_FILES)/parse
SRC_PIPE = $(SRC_FILES)/pipe
SRC_BUILDS = $(SRC_FILES)/builds

SRC = $(wildcard $(SRC_FILES)/*.c) \
      $(wildcard $(SRC_UTILS)/*.c) \
      $(wildcard $(SRC_ERRORS)/*.c) \
      $(wildcard $(SRC_LIBRARY)/*.c) \
      $(wildcard $(SRC_PARSING)/*.c) \
      $(wildcard $(SRC_PIPE)/*.c) \
	  $(wildcard $(SRC_BUILDS)/*.c)
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

all: libft/libft.a $(NAME)
	@echo "$(GREEN)✅ Compilación completada: $(NAME)$(RESET)"
	@toilet -f ivrit -F crop MINISHELL

libft/libft.a:
	@sleep 2
	@echo "$(BLUE)📦 Compilando libft...$(RESET)"
	@$(MAKE) --no-print-directory -C src/library
	@sleep 2

$(NAME): $(OBJ)
	@echo "$(BLUE)🔧 Enlazando objetos...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@sleep 2

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)🧹 Limpiando objetos...$(RESET)"
	@rm -f $(OBJ)
	@$(MAKE) --no-print-directory -C src/library clean
	@sleep 2

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C src/library fclean
	@sleep 2

re: fclean all

PHONY: all clean fclean re
