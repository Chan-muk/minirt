# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/23 12:04:47 by chajung           #+#    #+#              #
#    Updated: 2023/06/28 15:36:08 by chajung          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME		= miniRT

CC			= cc -O2
CFLAGS		= -Wall -Wextra -Werror
RMFLAGS		= -r

HEADER		= -I./inc
LMLX		= -lmlx
IMLX		= -Imlx
FRAMEWORK	= -framework OpenGL -framework AppKit
MLX_DIR		= -L./minilibx

LIB			= libft/libft.a
LIB_DIR		= libft

ALL_SRCS	= $(COM_SRCS) $(PAR_SRCS)
ALL_OBJS	= $(COM_OBJS) $(PAR_OBJS)

OBJ_DIR		= obj obj/parse
OBJ_B_DIR	= obj_b obj_b/parse
SRC_DIR		= src src/parse

ifeq ($(MAKECMDGOALS), bonus)
include inc/Makefile_bonus
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(LMLX) $(MLX_DIR) $(FRAMEWORK)
	@echo "make bonus done"

$(OBJ_B_DIR):
	@$(RM) $(RMFLAGS) $(OBJ_DIR) $(NAME)
	@mkdir -p $(OBJ_B_DIR)

else
include inc/Makefile_mandatory
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(LMLX) $(MLX_DIR) $(FRAMEWORK)
	@echo "make done"

$(OBJ_DIR):
	@$(RM) $(RMFLAGS) $(OBJ_B_DIR) $(NAME)
	@mkdir -p $(OBJ_DIR)
endif

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

all: $(OBJ_DIR) $(NAME)

bonus: $(OBJ_B_DIR) $(NAME)

clean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(OBJ_B_DIR)
	@$(MAKE) fclean -C $(LIB_DIR)
	@echo "make clean done"

fclean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(OBJ_B_DIR)
	@$(MAKE) fclean -C $(LIB_DIR)
	@echo "make fclean done"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re bonus
