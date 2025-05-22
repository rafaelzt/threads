# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/20 17:37:09 by rzt               #+#    #+#              #
#    Updated: 2025/05/20 17:51:56 by rzt              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -pthread
# CFLAGS += -fsanitize=address
RM = rm -rf

# Directories
BIN_DIR = bin
INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj

SRCS = \
	src/03_understanding_thread_sync.c
#	src/02_passing_args_struct_threads.c
#	src/00_creating_terminating_threads.c
#	src/01_passing_args_arr_threads.c
	

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = $(BIN_DIR)/thread

CFLAGS += -fsanitize=thread
all: $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) -f $(OBJ_DIR)/*

fclean: clean
	$(RM) -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
