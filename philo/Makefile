CC = gcc
CFLAGS = -Wall -Wextra -Werror

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = philo

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/

SRC_FILES = philo \
			utils \
			philo_utils

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n$(YELLOW)🔸 MAKING PROGRAM 🔸$(DEF_COLOR)\n"
	@echo "$(YELLOW)________  ___  ___  ___  ___       ________       $(DEF_COLOR)"
	@echo "$(YELLOW)|\   __  \|\  \|\  \|\  \|\  \     |\   __  \     $(DEF_COLOR)"
	@echo "$(YELLOW)\ \  \|\  \ \  \ \  \ \  \ \  \    \ \  \|\  \    $(DEF_COLOR)"
	@echo "$(YELLOW) \ \   ____\ \   __  \ \  \ \  \    \ \  \ \  \   $(DEF_COLOR)"
	@echo "$(YELLOW)  \ \  \___|\ \  \ \  \ \  \ \  \____\ \  \_\  \  $(DEF_COLOR)"
	@echo "$(YELLOW)   \ \__\    \ \__\ \__\ \__\ \_______\ \_______\ $(DEF_COLOR)"
	@echo "$(YELLOW)    \|__|     \|__|\|__|\|__|\|_______|\|_______| $(DEF_COLOR)\n"                                     
	@$(CC) $(CFLAGS) -lpthread $(OBJ) -o $@
	@echo "👉 $(BLUE)$(CC) $(CFLAGS) -lpthread $(OBJ) -o $@$(DEF_COLOR)"
	@echo "\n$(GREEN)✅ $(NAME) compiled!$(DEF_COLOR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "\n$(YELLOW)🔸 COMPILING 🔸$(DEF_COLOR)\n"
	@echo "🍩 $(MAGENTA)Compiling: $< $(DEF_COLOR)"
	@$(CC) -c $< $(CFLAGS) -I$(INC_DIR) -o $@

.PHONY: clean fclean

clean:
	@echo " "
	@echo "$(YELLOW)🔸 CLEAN 🔸$(DEF_COLOR)"
	@echo " "
	@rm -rf $(OBJ_DIR)
	@echo "🗑️  $(RED)rm -rf $(OBJ_DIR)$(DEF_COLOR)"
	@echo " "
	@echo "$(GREEN)✅ $(NAME) object files cleaned!$(DEF_COLOR)"

fclean: clean
	@echo " "
	@rm -rf $(NAME)
	@echo "🗑️  $(RED)rm -rf $(NAME)$(DEF_COLOR)"
	@echo " "
	@echo "$(GREEN)✅ $(NAME) executable files cleaned!$(DEF_COLOR)"
	@echo " "

re: fclean all