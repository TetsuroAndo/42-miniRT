# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 13:31:17 by teando            #+#    #+#              #
#    Updated: 2025/04/30 17:51:27 by tomsato          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= miniRT
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -rf

# ディレクトリ設定
ROOT_DIR		:= .
SRC_DIR			:= $(ROOT_DIR)/src
INC_DIR			:= $(ROOT_DIR)/inc
OBJ_DIR			:= $(ROOT_DIR)/obj
LIBFT_DIR		:= $(ROOT_DIR)/src/lib/libft
MLX_DIR			:= $(ROOT_DIR)/src/lib/minilibx

# FLAGS
DEFINE		:= -DDEBUG_MODE=DEBUG_NONE
IDFLAGS		:= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LFLAGS		:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# 環境依存
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBFT		:= $(LIBFT_DIR)/libft_mac.a
	MLX			:= $(MLX_DIR)/libmlx_Darwin.a
	IDFLAGS		+= OpenGL -framework AppKit -L/opt/X11/lib
else
	LIBFT		:= $(LIBFT_DIR)/libft.a
	MLX			:= $(MLX_DIR)/libmlx_Linux.a
endif

SRC		:= $(shell find $(SRC_DIR)/app -name '*.c')
SRC		+= $(shell find $(SRC_DIR)/lib/xlib -name '*.c')
OBJ		:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# dev all
all: CFLAGS += -g -fsanitize=address -O1 -fno-omit-frame-pointer
all: DEFINE := -DDEBUG_MODE=DEBUG_ALL
all: $(NAME)

ifeq ($(UNAME_S),Darwin)
$(NAME): setup_xquartz
endif
$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(IDFLAGS) $(LFLAGS) $(DEFINE) -o $(NAME)
	@echo "====================="
	@echo "== Build Complete! =="
	@echo "====================="
	@echo "[Executable]: $(NAME)"
	@echo "[UNAME_S]: $(UNAME_S)"
	@echo "[LIBRARY]: $(LIBFT) | $(MLX)"
	@echo "[INCLUDEDIR]: $(INC_DIR) | $(LIBFT_DIR) | $(MLX_DIR)"
	@echo "[Compiler flags/CFLAGS]: $(CFLAGS)"
	@echo "[Linker flags/LFLAGS]: $(LFLAGS)"
	@echo "[Debug flags/DEFINE]: $(DEFINE)"
	@echo "====================="

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT_DIR) $(MLX_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IDFLAGS) $(DEFINE) -fPIC -MMD -MP  -c $< -o $@

$(LIBFT): | $(LIBFT_DIR)/libft.h
	$(MAKE) -C $(LIBFT_DIR)

$(MLX): | $(MLX_DIR)/mlx.h
	$(MAKE) -C $(MLX_DIR)

c:
	$(RM) $(OBJ_DIR)
f: c
	$(RM) $(NAME)
r: f all

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(MLX_DIR)/libmlx.a $(MLX_DIR)/libmlx_Darwin.a $(MLX_DIR)/libmlx_Linux.a

re: fclean all

# =======================
# == PRODUCTION =========
# =======================

v: CFLAGS += -O2
v: f $(NAME)

# =======================
# == DEBUG =============
# =======================

core: CFLAGS += -g -fsanitize=address -O1 -fno-omit-frame-pointer
core: DEFINE := -DDEBUG_MODE=DEBUG_CORE
core: f $(NAME)

debug: CFLAGS += -g -fsanitize=address -O1 -fno-omit-frame-pointer
debug: DEFINE := -DDEBUG_MODE=DEBUG_ALL
debug: f $(NAME)
	@echo "====================="
	@echo "== Build Complete! =="
	@echo "====================="
	@echo "[Executable]: $(NAME)"
	@echo "[UNAME_S]: $(UNAME_S)"
	@echo "[LIBRARY]: $(LIBFT) $(MLX)"
	@echo "[INCLUDEDIR]: $(INC_DIR) $(LIBFT_DIR) $(MLX_DIR)"
	@echo "[Compiler flags/CFLAGS]: $(CFLAGS)"
	@echo "[Linker flags/LFLAGS]: $(LFLAGS)"
	@echo "[Debug flags/DEFINE]: $(DEFINE)"
	@echo "====================="

# =======================
# == Submodule Targets ==
# =======================

$(LIBFT_DIR)/libft.h:
	git submodule update --remote --init --recursive

$(MLX_DIR)/mlx.h:
	https://github.com/TetsuroAndo/42-miniRT.git

sub:
	git submodule update --remote

norm:
	@norminette $(SRC) $(INC_DIR)

# =======================
# == MACOS Setup ========
# =======================

setup_xquartz:
	@open -a XQuartz
	@export DISPLAY=:0

.PHONY: all clean fclean re
