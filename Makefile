# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 14:29:42 by frbranda          #+#    #+#              #
#    Updated: 2026/02/24 15:23:03 by frbranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                   SETTINGS                                   #
#==============================================================================#

NAME = ircserv

CC = c++

INC_DIRS = -Iinc \
			-Iinc/Channels \
			-Iinc/Clients \
			-Iinc/Commands \
			-Iinc/Core \
			-Iinc/Parsing \
			-Iinc/Utils

FLAGS = -Wall -Wextra -Werror -std=c++98 $(INC_DIRS)

RM = rm -rf

VAL = valgrind --leak-check=full --show-leak-kinds=all

#==============================================================================#
#                                    EXTRA                                     #
#==============================================================================#

ECHO = @echo
GREEN = \033[1;32m
RED = \033[1;31m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
YELLOW  = \033[1;33m
RESET = \033[0m

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

# Source Directories
VPATH = src
VPATH += src/Core
VPATH += src/Commands
VPATH += src/Utils
VPATH += src/Channels
VPATH += src/Clients


# Source Files
SRC = main.cpp 
CORE = Server.cpp
COMMANDS = ACommand.cpp CommandFactory.cpp
UTILS = Utils.cpp
CHANNELS = Channel.cpp
CLIENTS = Client.cpp


# Object Files
SRC += $(CORE)
SRC += $(COMMANDS)
SRC += $(UTILS)
SRC += $(CHANNELS)
SRC += $(CLIENTS)


OBJ_DIR = obj
OBJS = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(YELLOW)[Compiled]$(RESET) $<"

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "╔══════════════════════════╗"
	@echo "║ ✅ Compiled Successfully!║"
	@echo "╚══════════════════════════╝"

r: all
	@./$(NAME) 6667 123

rr: re
	@./$(NAME) 6667 123

rv: all
	@$(VAL) ./$(NAME) 6667 123

clean:
	@$(RM) $(OBJS)
	@echo "$(RED)[CLEAN] Object files removed.$(RESET)"

fclean: clean
	@$(RM) $(NAME) $(OBJ_DIR)
	@echo "$(RED)[FCLEAN] Binary removed.$(RESET)"

re: fclean all

# Phony Targets
.PHONY: all clean fclean re r rv