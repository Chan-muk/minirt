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

CC			= cc -g3 -O3
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
SRC_DIR		= src src/parse

PAR_DIR		= src/parse
PAR_SRC		= \
			parse.c _scene.c _objects.c _atod.c _split.c _utils0.c _utils1.c

PAR_OBJ_DIR	= obj/parse
PAR_OBJ		= $(PAR_SRC:.c=.o)
PAR_OBJS	= $(addprefix $(PAR_OBJ_DIR)/, $(PAR_OBJ))
PAR_SRCS	= $(addprefix $(PAR_DIR)/, $(PAR_SRC))

COM_DIR		= src
COM_SRC		= \
			main.c \
			init.c cal0.c cal1.c cal2.c scene.c color.c color_utils.c \
			hit.c phong.c texture.c bump.c\
			plane.c cylinder.c cylinder_utils.c sphere.c cone.c hook.c utils.c \

COM_OBJ_DIR = obj
COM_OBJS	= $(addprefix $(COM_OBJ_DIR)/, $(COM_OBJ))
COM_OBJ		= $(COM_SRC:.c=.o)
COM_SRCS	= $(addprefix $(COM_DIR)/, $(COM_SRC))

$(COM_OBJ_DIR)/%.o : $(COM_DIR)/%.c
	@$(CC) -c $< -o $@ $(IMLX) $(HEADER)

$(PAR_OBJ_DIR)/%.o : $(PAR_DIR)/%.c
	@$(CC) -c $< -o $@ $(IMLX) $(HEADER)


ifeq ($(MAKECMDGOALS), bonus)
# include inc/bns_mkfile
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(LIB) $^ -o $@ $(LMLX) $(MLX_DIR) $(FRAMEWORK)

$(OBJ_DIR):
	@$(RM) $(RMFLAGS) $(OBJ_B_DIR) $(NAME)
	@mkdir -p $(OBJ_DIR)
else
# include inc/var_mkfile
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(LIB) $^ -o $@ $(LMLX) $(MLX_DIR) $(FRAMEWORK)
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
	@$(RM) $(RMFLAGS) $(NAME) minishell.dSYM
	@echo "make fclean done"

re:
	@$(MAKE) fclean
	@$(MAKE) all

# .DEFAULT_GOAL := all

# NAME		= minirt

# CC			= cc -g3 -O3
# CFLAGS		= -Wall -Wextra -Werror
# RMFLAGS		= -r

# HEADER		= -I./inc
# LMLX		= -lmlx
# IMLX		= -Imlx
# FRAMEWORK	= -framework OpenGL -framework AppKit
# MLX_DIR		= -L./minilibx

# LIB			= libft/libft.a
# LIB_DIR		= libft

# SRC_DIR		= src
# OBJ_DIR		= obj

# SRC			= \
# 			main.c \
# 			init.c input.c cal.c scene.c color.c hit.c phong.c texture.c \
# 			plane.c cylinder.c sphere.c cone.c hook.c utils.c parse.c \

# # SRC_BONUS	= main_bonus.c

# OBJS		= $(addprefix $(OBJ_DIR)/, $(OBJ))

# ifeq ($(MAKECMDGOALS), bonus)
# SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_BONUS))
# OBJ			= $(SRC_BONUS:.c=.o)
# else
# SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))
# OBJ			= $(SRC:.c=.o)
# endif

# all: $(OBJ_DIR) $(NAME)
# bonus: $(OBJ_DIR) $(NAME)

# $(NAME): $(OBJS) $(LIB)
# 	$(CC) $(LIB) $^ -o $@ $(LMLX) $(MLX_DIR) $(FRAMEWORK)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) -c $< -o $@ $(IMLX) $(HEADER)

# # $(NAME): $(OBJS) $(LIB)
# # 	$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(LMLX) $(MLX_DIR) $(FRAMEWORK)

# # $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# # 	$(CC) $(CFLAGS) -c $< -o $@ $(IMLX) $(HEADER)

# $(OBJ_DIR):
# 	mkdir $(OBJ_DIR)

# $(LIB):
# 	$(MAKE) -C $(LIB_DIR)

# clean:
# 	$(RM) $(RMFLAGS) $(OBJ_DIR)
# 	$(MAKE) fclean -C $(LIB_DIR)

# fclean: clean
# 	$(RM) $(RMFLAGS) $(NAME)

# re:
# 	$(MAKE) fclean
# 	$(MAKE) all

# .PHONY: all clean fclean re bonus
