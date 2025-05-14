ROOT      := ../..
UNAME_S   := $(shell uname -s)
OBJ_DIR   := $(ROOT)/obj
SRC_DIR   := $(ROOT)/src
INC_DIR   := $(ROOT)/inc
XLIB_DIR  := $(SRC_DIR)/lib/xlib
PARSE_DIR := $(SRC_DIR)/modules/parse
LIBFT_DIR := $(SRC_DIR)/lib/libft

ifeq ($(UNAME_S),Darwin)
	LIBFT := $(LIBFT_DIR)/libft_mac.a
else
	LIBFT := $(LIBFT_DIR)/libft.a
endif

# Homebrew でインストールされた GoogleTest を使用
GTEST_PREFIX := /opt/homebrew/opt/googletest
GTEST_INC := $(GTEST_PREFIX)/include
GTEST_LIB := -L$(GTEST_PREFIX)/lib -lgtest -lgtest_main -pthread

# テスト環境を示すマクロ定義
DEFINE_FLAGS := -DTEST_MODE=1 -DDEBUG_MODE=DEBUG_NONE

# Cコンパイラフラグ
CFLAGS := -std=gnu11 -Wall -Wextra -Werror $(DEFINE_FLAGS)

# インクルードディレクトリ
IDFLAGS := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(GTEST_INC) -I.

# ソースファイルのリスト
SRC_C    := $(wildcard $(XLIB_DIR)/*.c) $(wildcard $(PARSE_DIR)/*.c) $(CURDIR)/stub_exit.c $(CURDIR)/test_main.c

# オブジェクトファイルのリスト
OBJ_C    := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter $(SRC_DIR)/%, $(SRC_C)))
OBJ_LOCAL := $(patsubst $(CURDIR)/%.c, $(OBJ_DIR)/test/parser/%.o, $(filter $(CURDIR)/%, $(SRC_C)))
OBJ      := $(OBJ_C) $(OBJ_LOCAL)

all: parser_tests

# ディレクトリ作成用ルール
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IDFLAGS) -c $< -o $@

$(OBJ_DIR)/test/parser/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IDFLAGS) -c $< -o $@

parser_tests: $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ) parser_tests $(OBJ_DIR)

re: clean all
.PHONY: all clean re