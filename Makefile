# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/23 12:04:47 by chajung           #+#    #+#              #
#    Updated: 2023/04/23 12:04:49 by chajung          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME		= minirt

CC			= cc -g3
CFLAGS		= -Wall -Wextra -Werror -g3
RMFLAGS		= -r

HEADER		= -I./inc
LMLX		= -lmlx
IMLX		= -Imlx
FRAMEWORK	= -framework OpenGL -framework AppKit
MLX_DIR		= -L./minilibx

LIB			= libft/libft.a
LIB_DIR		= libft

SRC_DIR		= src
OBJ_DIR		= obj

SRC			= \
			main.c input.c plain.c sphere.c scatter.c color.c random.c init.c hook.c cal.c utils.c

SRC_BONUS	= main_bonus.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(OBJ))

ifeq ($(MAKECMDGOALS), bonus)
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_BONUS))
OBJ			= $(SRC_BONUS:.c=.o)
else
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))
OBJ			= $(SRC:.c=.o)
endif

all: $(OBJ_DIR) $(NAME)
bonus: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(LIB) $^ -o $@ $(LMLX) $(MLX_DIR) $(FRAMEWORK)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(IMLX) $(HEADER)


# $(NAME): $(OBJS) $(LIB)
# 	$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(LMLX) $(MLX_DIR) $(FRAMEWORK)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@ $(IMLX) $(HEADER)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)
	$(MAKE) fclean -C $(LIB_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus
