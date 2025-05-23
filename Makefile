# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 13:31:17 by teando            #+#    #+#              #
#    Updated: 2025/05/24 01:16:52 by teando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= miniRT
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -rf

# Project PATH
ROOT_DIR		:= .
SRC_DIR			:= $(ROOT_DIR)/src
INC_DIR			:= $(ROOT_DIR)/inc
OBJ_DIR			:= $(ROOT_DIR)/obj
LIBFT_DIR		:= $(ROOT_DIR)/src/lib/libft
MLX_DIR			:= $(ROOT_DIR)/src/lib/minilibx
CONF_DIR		:= $(ROOT_DIR)/config
CONF			:= $(CONF_DIR)/minirt.conf
CONF_SAMP		:= $(CONF_DIR)/minirt.conf.sample

# FLAGS
IDFLAGS		:= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LFLAGS		:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Environment Dependent
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
SRC		+= $(shell find $(SRC_DIR)/modules/camera -name '*.c')
SRC		+= $(shell find $(SRC_DIR)/modules/render -name '*.c')
SRC		+= $(shell find $(SRC_DIR)/modules/hit -name '*.c')
OBJ		:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# =======================
# == Targets =============
# =======================
all:
	$(MAKE) __build -j $(shell nproc)

ifeq ($(UNAME_S),Darwin)
__build: setup_xquartz
__build: conf_get $(NAME)
else
__build: conf_get $(NAME)
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
	@echo "[DEFINE]: $(DEFINE)"
	@echo "[Window size]: $(WIDTH_DEF) x $(HEIGHT_DEF)"
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
# == Submodule Targets ==
# =======================

$(LIBFT_DIR)/libft.h:
	git submodule update --remote --init --recursive

$(MLX_DIR)/mlx.h:
	git submodule update --init --recursive

sub:
	git submodule update --remote

# =======================
# == Dev Tool Targets ===
# =======================

norm:
	@norminette $(SRC) $(INC_DIR)

nm:
	@nm $(OBJ) | grep ' U ' | awk '{print $$2}' | sort | uniq

nmbin:
	@nm $(NAME) | grep ' U ' | awk '{print $$2}' | sort | uniq

printsrc:
	@echo $(SRC) | tr ' ' '\n' | sort

printobj:
	@echo $(OBJ) | tr ' ' '\n' | sort

# =======================
# == Config Targets =====
# =======================

$(CONF):
	@mkdir -p $(CONF_DIR)
	@if [ ! -f $(CONF_SAMP) ]; then \
		echo "Warning: Sample config file $(CONF_SAMP) not found. Creating a default one."; \
		echo "CFLAGS=-O3" > $(CONF); \
		echo "WIDTH=1280" >> $(CONF); \
		echo "HEIGHT=720" >> $(CONF); \
	elif [ ! -f $(CONF) ]; then \
		echo "Creating default config file from sample..."; \
		cp $(CONF_SAMP) $(CONF); \
	fi

conf_get: $(CONF)
	$(eval WIDTH_DEF := $(shell cat $(CONF) | grep WIDTH | cut -d'=' -f2 || echo 960))
	$(eval HEIGHT_DEF := $(shell cat $(CONF) | grep HEIGHT | cut -d'=' -f2 || echo 540))
	$(eval DEFINE := -DWIDTH=$(WIDTH_DEF) -DHEIGHT=$(HEIGHT_DEF))
	$(eval CFLAGS := $(if $(findstring -O, $(CFLAGS)), $(CFLAGS), $(CFLAGS) $(shell cat $(CONF) | grep CFLAGS | sed 's/CFLAGS=//')))

conf: $(CONF)

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
