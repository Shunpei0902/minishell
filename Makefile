NAME := minishell

LIBFT = ./libft
SDIR := src/
ODIR := obj/
IDIR := inc/
SRCS := error.c free.c main.c parser.c redirect.c tokenizer.c pipe.c expand.c signal.c builtin.c b_cd.c b_echo.c b_env.c b_exit.c b_unset.c b_export.c hashmap.c
OBJS := $(SRCS:%.c=$(ODIR)%.o)
# INCS = -DREADLINE_LIBRARY -I$(IDIR) -I$(LIBFT)
DEPS = $(patsubst %.o,%.d, $(OBJS))
DEPFLAGS := -MMD -MP
# LDFLAGS := -lreadline -L$(LIBFT) -lft
# CFLAGS = -Wall -Wextra -Werror $(DEPFLAGS) -std=c99
CC := cc
MKDIR := mkdir -p
OS = $(shell uname)

READLINE_DIR := $(shell brew --prefix readline)

# rl_replace_lineがmacOSのreadlineライブラリには存在しないため、brewからインストールしたreadlineを使う
LDFLAGS := -L$(LIBFT) -lft -L$(READLINE_DIR)/lib -lreadline
INCS := -DREADLINE_LIBRARY -I$(IDIR) -I$(LIBFT) -I$(READLINE_DIR)/include

ifdef WITH_LEAKS
	CFLAGS += -DLEAK_CHECK -g3 -O0
endif
ifdef WITH_ASAN
	CFLAGS += -fsanitize=address -g3 -O0
endif
ifdef WITH_NDEF
	CFLAGS += -fsanitize=undefined -g3 -O0
endif
ifeq ($(OS), Linux)
	LDFLAGS +=
	CFLAGS += -D__Linux__
endif
ifeq ($(OS), Darwin)
	LDFLAGS +=
	CFLAGS += -D__Apple__
endif

all: $(NAME)

$(NAME): $(OBJS) | ft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

ft:
	@make -C $(LIBFT)

$(ODIR)%.o:$(SDIR)%.c | $(ODIR)
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

$(ODIR):
	@echo "Creating directory: $(ODIR)"
	$(MKDIR) $@

clean:
	@make $@ -C $(LIBFT)
	rm -rf $(ODIR)

fclean: clean
	@make $@ -C $(LIBFT)
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean
	@make all

norm: requirements.txt
	pip3 list --outdated
	norminette $(addprefix $(SDIR), $(SRCS)) $(IDIR)*.h

fmt:
	c_formatter_42 $(addprefix $(SDIR), $(SRCS)) $(IDIR)*.h

deps:
	nm -u $(NAME)

l: fclean
	@make WITH_LEAKS=1

san: fclean
	@make WITH_ASAN=1 WITH_NDEF=1

v: all
	valgrind $(NAME)

-include $(DEPS)

.PHONY: all clean fclean re
