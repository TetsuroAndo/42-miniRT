# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 13:31:17 by teando            #+#    #+#              #
#    Updated: 2025/05/05 10:26:23 by teando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= parser_test
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g $(ASAN_FLAGS) -O1 -fno-omit-frame-pointer
RM			:= rm -rf

# ディレクトリ設定
ROOT_DIR		:= .
SRC_DIR			:= $(ROOT_DIR)
INC_DIR			:= $(ROOT_DIR)/../../inc
OBJ_DIR			:= $(ROOT_DIR)/obj
LIBFT_DIR		:= $(ROOT_DIR)/../../src/lib/libft

# FLAGS
DEFINE		:= -DDEBUG_MODE=DEBUG_ALL
IDFLAGS		:= -I$(INC_DIR) -I$(LIBFT_DIR)

# 環境依存
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBFT		:= $(LIBFT_DIR)/libft_mac.a
	# MacOSではAddressSanitizerのリンクフラグが異なる
	ASAN_FLAGS := -fsanitize=address
else
	LIBFT		:= $(LIBFT_DIR)/libft.a
	ASAN_FLAGS := -fsanitize=address
endif

# テスト用ソースファイル
SRC		:= $(shell find $(SRC_DIR) -name '*.c')

# テスト用ソースファイルのみを対象にする
TEST_SRC	:= $(shell find $(SRC_DIR) -maxdepth 1 -name '*.c')

# パーサーモジュールのソースファイル
PARSER_SRC	:= $(shell find $(SRC_DIR)/../../src/modules/parse/ -name '*.c')
XLIB_SRC	:= $(shell find $(SRC_DIR)/../../src/lib/xlib/ -name '*.c')

# 各ソースファイルに対応するオブジェクトファイルのパスを生成
TEST_OBJ	:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRC))
PARSER_OBJ	:= $(patsubst $(SRC_DIR)/../../src/modules/parse/%.c,$(OBJ_DIR)/modules_parse_%.o,$(PARSER_SRC))
XLIB_OBJ	:= $(patsubst $(SRC_DIR)/../../src/lib/xlib/%.c,$(OBJ_DIR)/lib_xlib_%.o,$(XLIB_SRC))

# すべてのオブジェクトファイルを結合
OBJ		:= $(TEST_OBJ) $(PARSER_OBJ) $(XLIB_OBJ)

# ログファイル
LOG_FILE := parser_test.log

# テスト実行ルール
all: $(NAME)

test: $(NAME)
	./$(NAME)
	@echo "\nTest log saved to $(LOG_FILE)"

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(IDFLAGS) $(DEFINE) -lm -o $(NAME)
	@echo "====================="
	@echo "== Build Complete! =="
	@echo "====================="
	@echo "[Executable]: $(NAME)"
	@echo "[UNAME_S]: $(UNAME_S)"
	@echo "[LIBRARY]: $(LIBFT)"
	@echo "[INCLUDEDIR]: $(INC_DIR) | $(LIBFT_DIR)"
	@echo "[Compiler flags/CFLAGS]: $(CFLAGS)"
	@echo "[Debug flags/DEFINE]: $(DEFINE)"
	@echo "====================="

# テスト用ソースファイルのコンパイルルール
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IDFLAGS) $(DEFINE) -fPIC -MMD -MP -c $< -o $@

# パーサーモジュールのソースファイルのコンパイルルール
$(OBJ_DIR)/modules_parse_%.o: $(SRC_DIR)/../../src/modules/parse/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IDFLAGS) $(DEFINE) -fPIC -MMD -MP -c $< -o $@

# xlibのソースファイルのコンパイルルール
$(OBJ_DIR)/lib_xlib_%.o: $(SRC_DIR)/../../src/lib/xlib/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IDFLAGS) $(DEFINE) -fPIC -MMD -MP -c $< -o $@

$(LIBFT): | $(LIBFT_DIR)/libft.h
	$(MAKE) -C $(LIBFT_DIR)

c:
	$(RM) $(OBJ_DIR)
	f: c
	$(RM) $(NAME)
	$(RM) $(LOG_FILE)

r: f all

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LOG_FILE)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# =======================
# == Submodule Targets ==
# =======================

$(LIBFT_DIR)/libft.h:
	git submodule update --remote --init --recursive

sub:
	git submodule update --remote

norm:
	@norminette $(SRC) $(INC_DIR)

.PHONY: all test c f r clean fclean re sub norm
