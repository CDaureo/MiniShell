NAME = minishell

SRC_FILES = ./src
SRC_UTILS = $(SRC_FILES)/utils
SRC_LIBRARY = $(SRC_FILES)/library
SRC_ERRORS = $(SRC_FILES)/errors
SRC_PARSING = $(SRC_FILES)/parse
SRC_PIPE = $(SRC_FILES)/pipe
SRC_BUILDS = $(SRC_FILES)/builds

SRC = $(SRC_FILES)/main.c \
	  $(SRC_UTILS)/free_simple_cmds.c \
	  $(SRC_UTILS)/signals.c \
	  $(SRC_UTILS)/envp_utils.c \
	  $(SRC_UTILS)/prompt_utils.c \
	  $(SRC_UTILS)/quotes_utils.c \
	  $(SRC_UTILS)/cmd_utils.c \
      $(SRC_ERRORS)/errors.c \
      $(SRC_PARSING)/parse.c \
      $(SRC_PARSING)/handlers.c \
      $(SRC_PARSING)/token_helpers.c \
	  $(SRC_PARSING)/commands.c \
      $(SRC_PIPE)/pipex.c \
	  $(SRC_PIPE)/free_paths.c \
	  $(SRC_PIPE)/get_paths.c \
      $(SRC_PIPE)/redirections.c \
      $(SRC_BUILDS)/echo.c \
      $(SRC_BUILDS)/env.c \
      $(SRC_BUILDS)/envp.c \
      $(SRC_BUILDS)/export.c \
	  $(SRC_BUILDS)/pwd.c \
	  $(SRC_BUILDS)/cd.c \
	  $(SRC_BUILDS)/handle_builds.c \
	  $(SRC_BUILDS)/unset.c \
	  $(SRC_BUILDS)/isbuilds.c



OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIE
LDFLAGS = -lreadline -pie -Lsrc/library -lft

GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

all: banner libft/libft.a $(NAME)
	@echo "$(GREEN)✅ Compilación completada: $(NAME)$(RESET)"
# @toilet -f ivrit -F crop MINISHELL

banner:
	@echo "$(GREEN) _   .-')                 .-') _          .-')    ('-. .-.   ('-. $(RESET)"
	@echo "$(GREEN)( '.( OO )_              ( OO ) )        ( OO ). ( OO )  / _(  OO)$(RESET)"
	@echo "$(GREEN) ,--.   ,--.) ,-.-') ,--./ ,--,' ,-.-') (_)---\_),--. ,--.(,------.,--.      ,--.$(RESET)"
	@echo "$(GREEN) |   \`.'   |  |  |OO)|   \ |  |\ |  |OO)/    _ | |  | |  | |  .---'|  |.-')  |  |.-')$(RESET)"
	@echo "$(GREEN) |         |  |  |  \|    \|  | )|  |  \\\  :\` \`.  |   .|  | |  |    |  | OO ) |  | OO )$(RESET)"
	@echo "$(GREEN) |  |'.'|  |  |  |(_/|  .     |/ |  |(_/ '..\`''.)|       |(|  '--. |  |\`-' | |  |\`-' |$(RESET)"
	@echo "$(GREEN) |  |   |  | ,|  |_.'|  |\    | ,|  |_.'.-._)   \|  .-.  | |  .--'(|  '---.'(|  '---.'$(RESET)"
	@echo "$(GREEN) |  |   |  |(_|  |   |  | \   |(_|  |   \       /|  | |  | |  \`---.|      |  |      |$(RESET)"
	@echo "$(GREEN) \`--'   \`--'  \`--'   \`--'  \`--'  \`--'    \`-----' \`--' \`--' \`------'\`------'  \`------'$(RESET)"

libft/libft.a:
	@$(MAKE) --no-print-directory -C src/library

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo "$(BLUE)🔧 Enlazando objetos...$(RESET)"
	@sleep 2

%.o: %.c
	@echo "$(YELLOW)🛐 Que funcione por la virgencita del carmen....$(RESET)"
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
