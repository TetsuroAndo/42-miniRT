# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 13:31:17 by teando            #+#    #+#              #
#    Updated: 2025/05/09 03:05:54 by teando           ###   ########.fr        #
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
	LFLAGS		+= -framework OpenGL -framework AppKit -L/opt/X11/lib
else
	LIBFT		:= $(LIBFT_DIR)/libft.a
	MLX			:= $(MLX_DIR)/libmlx_Linux.a
endif

SRC		:= $(shell find $(SRC_DIR)/app -name '*.c')
SRC		+= $(shell find $(SRC_DIR)/lib/xlib -name '*.c')
SRC		+= $(shell find $(SRC_DIR)/modules/parse -name '*.c')
SRC		+= $(shell find $(SRC_DIR)/modules/render -name '*.c')
OBJ		:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# =======================
# == Targets =============
# =======================
all:
	$(MAKE) __all -j $(shell nproc)
v: f
	$(MAKE) __v -j $(shell nproc)
core: f
	$(MAKE) __core -j $(shell nproc)
debug: f
	$(MAKE) __debug -j $(shell nproc)

__all: CFLAGS += -g -fsanitize=address -O1 -fno-omit-frame-pointer
__all: DEFINE := -DDEBUG_MODE=DEBUG_ALL
__all: __build
ifeq ($(UNAME_S),Darwin)
__build: setup_xquartz
__build: $(NAME)
else
__build: $(NAME)
endif

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(IDFLAGS) $(LFLAGS) $(DEFINE) -o $(NAME)
	@echo "====================="
	@echo "== Build Complete! =="
	@echo "====================="
	@echo "[Executable]: $(NAME)"
	@echo "[UNAME_S]: $(UNAME_S)"
	@echo "[Library]: $(LIBFT) | $(MLX)"
	@echo "[IncludeDir]: $(INC_DIR) | $(LIBFT_DIR) | $(MLX_DIR)"
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

__v: CFLAGS += -O2
__v: DEFINE := -DDEBUG_MODE=DEBUG_NONE
__v: __build

# =======================
# == DEBUG =============
# =======================

__core: CFLAGS += -g -fsanitize=address -O1 -fno-omit-frame-pointer
__core: DEFINE := -DDEBUG_MODE=DEBUG_CORE
__core: __build

__debug: CFLAGS += -g -fsanitize=address -O1 -fno-omit-frame-pointer
__debug: DEFINE := -DDEBUG_MODE=DEBUG_ALL
__debug: __build

# =======================
# == Submodule Targets ==
# =======================

$(LIBFT_DIR)/libft.h:
	git submodule update --remote --init --recursive

$(MLX_DIR)/mlx.h:
	git submodule update --init --recursive

sub:
	git submodule update --remote

norm:
	@norminette $(SRC) $(INC_DIR)

# =======================
# == MACOS Setup ========
# =======================

setup_xquartz:
	@open -a XQuartz
	@if [ -z "$$DISPLAY" ]; then \
		echo "Setting DISPLAY environment variable..."; \
		export DISPLAY=:0; \
	fi

.PHONY: all clean fclean re
