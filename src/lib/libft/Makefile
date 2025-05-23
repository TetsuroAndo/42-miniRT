#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 18:09:17 by teando            #+#    #+#              #
#    Updated: 2025/04/23 19:26:03 by teando           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

UNAME_OS	:= $(shell uname -s)
NAME		:= libft.a
NAME_MAC	:= libft_mac.a
AR			:= ar rc
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -rf
LIBFT_H		:= libft.h
ROOT_DIR	:= .
OUT_DIR		:= $(ROOT_DIR)/out
OUT_MAC_DIR	:= $(ROOT_DIR)/out_mac
INCS_DIR	:= $(ROOT_DIR)/incs
IDFLAGS		:= -I$(INCS_DIR)

ifeq ($(UNAME_OS), Darwin)
NAME_SO		:= libft.dylib
else
NAME_SO		:= libft.so
endif

SRCS 		:= \
	$(addprefix $(ROOT_DIR)/, \
		$(addprefix ft_btree/, \
			ft_btree_clear.c \
			ft_btree_del_node.c \
			ft_btree_apply_by_level.c \
			ft_btree_apply_infix.c \
			ft_btree_apply_prefix.c \
			ft_btree_apply_suffix.c \
			ft_btree_create_node.c \
			ft_btree_insert_data.c \
			ft_btree_level_count.c \
			ft_btree_search_item.c \
		) \
		$(addprefix ft_ctype/, \
			ft_isalnum_under.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isbackslash.c \
			ft_isblank.c \
			ft_iscntrl.c \
			ft_isdigit.c \
			ft_isgraph.c \
			ft_islower.c \
			ft_ismetachr.c \
			ft_isprint.c \
			ft_ispunct.c \
			ft_isspace.c \
			ft_isupper.c \
			ft_isxdigit.c \
			ft_tolower.c \
			ft_toupper.c \
		) \
		$(addprefix ft_gc/, \
			$(addprefix alloc/, \
				ft_gc_calloc.c \
				ft_gc_free.c \
				ft_gc_malloc.c \
			) \
			$(addprefix debug/, \
				ft_gc_count_data.c \
				ft_gc_dump.c \
				ft_gc_free_info.c \
			) \
			$(addprefix lst/, \
				ft_gc_clear.c \
				ft_gc_destroy.c \
				ft_gc_free_data.c \
				ft_gc_free_nodes.c \
				ft_gc_init.c \
				ft_gc_track.c \
				ft_gc_untrack.c \
			) \
			$(addprefix string/, \
				ft_strdup_gc.c \
				ft_strjoin_gc.c \
				ft_strtrim_gc.c \
				ft_substr_gc.c \
				str_n_cpy_gc.c \
			) \
		) \
		$(addprefix ft_stdio/, \
			ft_putchar_fd.c \
			ft_putchar.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_putstrs_endl_fd.c \
			ft_putstrs_fd.c \
			$(addprefix ft_dprintf/, \
				ft_dprintf.c \
				ft_printf.c \
				type_putbase.c \
				type_putchar.c \
				type_putptr.c \
				type_putstr.c \
			) \
		) \
		$(addprefix ft_stdlib/, \
			ft_abs.c \
			ft_atoi.c \
			ft_atol.c \
			ft_calloc.c \
			ft_itoa.c \
			ft_ltoa.c \
			ft_orealloc.c \
			ft_oreallocf.c \
			ft_strs_clear.c \
			ft_qsort.c \
			ft_strtol.c \
			ft_strtoll.c \
			ft_utoa.c \
		) \
		$(addprefix ft_string/, \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_memswap.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strcspn.c \
			ft_strdup.c \
			ft_strdup2.c \
			ft_strfunc.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strjoin2.c \
			ft_strjoin3.c \
			ft_strjoin_free.c \
			ft_strjoin_free2.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strndup.c \
			ft_strndupex.c \
			ft_strnlen.c \
			ft_strnstr.c \
			ft_strpbrk.c \
			ft_strrchr.c \
			ft_strrev.c \
			ft_strspn.c \
			ft_strstr.c \
			ft_strtok.c \
			ft_strtok_r.c \
			ft_strtrim.c \
			ft_substr.c \
		) \
		$(addprefix ft_strings/, \
			ft_bzero.c \
			ft_strcasecmp.c\
			ft_strncasecmp.c\
		) \
		$(addprefix ft_utils/, \
			ft_count_strs.c \
			ft_count_words.c \
			ft_isinset.c \
			ft_substr_l.c \
			ft_substr_r.c \
			ft_max.c \
			ft_min.c \
			ft_strs_dup.c \
			ft_swap.c \
			ft_swapint.c \
		) \
		$(addprefix get_next_line/, \
			get_next_line.c \
		) \
	)
BONUS_SRC	:= \
	$(addprefix $(ROOT_DIR)/, \
		$(addprefix ft_lst/, \
			ft_create_elem.c \
			ft_list_at.c \
			ft_list_find.c \
			ft_list_foreach.c \
			ft_list_foreach_if.c \
			ft_list_from_strs.c \
			ft_list_last.c \
			ft_list_merge.c \
			ft_list_remove_if.c \
			ft_list_reverse.c \
			ft_list_size.c \
			ft_list_sort.c \
			ft_list_to_strs.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdel_front.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_sorted_list_insert.c \
			ft_sorted_list_merge.c \
		) \
	)
OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))
BONUS_OBJ	:= $(addprefix $(OUT_DIR)/, $(BONUS_SRC:.c=.o))
BONUS_DEPS	:= $(addprefix $(OUT_DIR)/, $(BONUS_SRC:.c=.d))
OBJS		+= $(BONUS_OBJ)
DEPS		+= $(BONUS_DEPS)

OBJS_MAC	:= $(addprefix $(OUT_MAC_DIR)/, $(SRCS:.c=.o))
DEPS_MAC	:= $(addprefix $(OUT_MAC_DIR)/, $(SRCS:.c=.d))
BONUS_OBJ_MAC	:= $(addprefix $(OUT_MAC_DIR)/, $(BONUS_SRC:.c=.o))
BONUS_DEPS_MAC	:= $(addprefix $(OUT_MAC_DIR)/, $(BONUS_SRC:.c=.d))
OBJS_MAC	+= $(BONUS_OBJ_MAC)
DEPS_MAC	+= $(BONUS_DEPS_MAC)

ifeq ($(DEBUG), 1)
CFLAGS		+= -g
else
CFLAGS		+= -O2
endif

all:
ifeq ($(UNAME_OS), Darwin)
	@$(MAKE) platform_mac
else
	@$(MAKE) $(NAME)
endif

platform_mac: $(NAME_MAC)

$(NAME): $(OBJS)
	$(AR) $@ $^

$(NAME_MAC): $(OBJS_MAC)
	$(AR) $@ $^

$(OUT_DIR)/%.o: %.c $(LIBFT_H)
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -fPIC -MMD -MP $(IDFLAGS) $< -o $@

$(OUT_MAC_DIR)/%.o: %.c $(LIBFT_H)
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -fPIC -DPLATFORM_MAC -MMD -MP $(IDFLAGS) $< -o $@

so: $(NAME_SO)

$(NAME_SO): $(OBJS)
ifeq ($(UNAME_OS), Darwin)
	$(CC) -shared -Wl,-install_name,@rpath/$@ $^ -o $@
else
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(IDFLAGS)
	gcc -nostartfiles -shared -o $(NAME_SO) $(OBJS)
endif

clean:
	$(RM) $(OUT_DIR) $(OUT_MAC_DIR)

fclean: clean
	$(RM) -f $(NAME) $(NAME_MAC) $(NAME_SO) a.out

re: fclean all

norm: $(LIBFT_H) $(INCS_DIR) $(SRCS) $(BONUS_SRC)
	@norminette $^

test: test.c
	$(CC) -g -fsanitize=address $< -o $@ -I. -Wl,-rpath . -L. -lft -lm

-include $(DEPS) $(DEPS_MAC)

.PHONY: all clean fclean fclean_all re bonus norm test platform_mac
