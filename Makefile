# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frbranda <frbranda@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 14:29:42 by frbranda          #+#    #+#              #
#    Updated: 2026/01/23 17:25:27 by frbranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                   SETTINGS                                   #
#==============================================================================#

SERVER = server
CLIENT = client

CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 -Iincludes

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

VPATH = src
VPATH += src/Server
VPATH += src/Client

# Source Files
SERVER_SRC = Server.cpp
CLIENT_SRC = Client.cpp

# Object Files
OBJ_DIR = obj
SERVER_OBJS = $(SERVER_SRC:%.cpp=$(OBJ_DIR)/%.o)
CLIENT_OBJS = $(CLIENT_SRC:%.cpp=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: $(SERVER) $(CLIENT)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(YELLOW)[Compiled]$(RESET) $<"

$(SERVER): $(SERVER_OBJS)
	@$(CC) $(FLAGS) $(SERVER_OBJS) -o $(SERVER)
	@echo "╔══════════════════════════╗"
	@echo "║ ✅ Server Compiled!      ║"
	@echo "╚══════════════════════════╝"

$(CLIENT): $(CLIENT_OBJS)	
	@$(CC) $(FLAGS) $(CLIENT_OBJS) -o $(CLIENT)
	@echo "╔══════════════════════════╗"
	@echo "║ ✅ Client Compiled!      ║"
	@echo "╚══════════════════════════╝"


rs: $(SERVER)
	@./$(SERVER)

rc: $(CLIENT)
	@./$(CLIENT)

rvs: $(SERVER)
	@$(VAL) ./$(SERVER)

rvc: $(CLIENT)
	@$(VAL) ./$(CLIENT)

clean:
	@$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
	@echo "$(RED)[CLEAN] Object files removed.$(RESET)"

fclean: clean
	@$(RM) $(SERVER) $(CLIENT) $(OBJ_DIR)
	@echo "$(RED)[FCLEAN] Binary removed.$(RESET)"

re: fclean all

# Phony Targets
.PHONY: all clean fclean re rs rc rvs rvc
