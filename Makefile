# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 13:31:17 by teando            #+#    #+#              #
#    Updated: 2025/05/23 20:50:31 by teando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= miniRT
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g -fsanitize=address -O1 -fno-omit-frame-pointer
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

# Window size
WIDTH_DEF	:= 1280
HEIGHT_DEF	:= 720

# FLAGS
IDFLAGS		:= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LFLAGS		:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
DEFINE		:= -DWIDTH=$(WIDTH_DEF) -DHEIGHT=$(HEIGHT_DEF)

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

SRC		:= \
		./src/app/finalize.c \
		./src/app/hooks.c \
		./src/app/initialize.c \
		./src/app/main.c \
		./src/lib/xlib/ft_strtod.c \
		./src/lib/xlib/vec_utils_1.c \
		./src/lib/xlib/vec_utils_2.c \
		./src/lib/xlib/vec_utils_3.c \
		./src/lib/xlib/xcalloc.c \
		./src/lib/xlib/xclose.c \
		./src/lib/xlib/xfree.c  \
		./src/lib/xlib/xgc_init.c \
		./src/lib/xlib/xget_next_line.c \
		./src/lib/xlib/xmalloc.c \
		./src/lib/xlib/xopen.c \
		./src/lib/xlib/xstrdup.c \
		./src/lib/xlib/xstrtrim.c \
		./src/modules/camera/cam_key.c \
		./src/modules/camera/cam_move.c \
		./src/modules/camera/vec_rot.c \
		./src/modules/hit/cy/cylinder_cap.c \
		./src/modules/hit/cy/cylinder_side.c \
		./src/modules/hit/cy/cylinder.c \
		./src/modules/hit/pl/plane.c \
		./src/modules/hit/sp/sphere.c \
		./src/modules/parse/obj_cylinder.c \
		./src/modules/parse/obj_plane.c \
		./src/modules/parse/obj_sphere.c \
		./src/modules/parse/parse_f64.c \
		./src/modules/parse/parse_rgb.c \
		./src/modules/parse/parse_vec3.c \
		./src/modules/parse/parser.c \
		./src/modules/parse/s_ambient.c \
		./src/modules/parse/s_camera.c \
		./src/modules/parse/s_light.c \
		./src/modules/parse/utils.c \
		./src/modules/render/calculate_light_color.c \
		./src/modules/render/calculate_lights_utils.c \
		./src/modules/render/color_convert.c \
		./src/modules/render/get_ray_direction.c \
		./src/modules/render/render.c \
		./src/modules/render/trace_ray.c
OBJ		:= $(patsubst ./%.c,$(OBJ_DIR)/%.o,$(SRC))

# =======================
# == Targets ============
# =======================

ifeq ($(UNAME_S),Darwin)
all: setup_xquartz $(NAME)
else
all: $(NAME)
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

$(OBJ_DIR)/%.o: ./%.c $(LIBFT_DIR) $(MLX_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IDFLAGS) $(DEFINE) -fPIC -MMD -MP  -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX): | $(MLX_DIR)
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
# == minilibx Targets ==
# =======================

$(MLX_DIR):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

mlxrm:
	rm -rf $(MLX_DIR)

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
# == MACOS Setup ========
# =======================

setup_xquartz:
	@open -a XQuartz
	@if [ -z "$$DISPLAY" ]; then \
		echo "Setting DISPLAY environment variable..."; \
		export DISPLAY=:0; \
	fi

.PHONY: all clean fclean re
