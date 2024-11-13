NAME := minishell

LIBFT = ./libft
SDIR := src/
ODIR := obj/
IDIR := inc/
SRCS := error.c free.c main.c parser.c redirect.c tokenizer.c pipe.c
OBJS := $(SRCS:%.c=$(ODIR)%.o)
INCS = -DREADLINE_LIBRARY -I$(IDIR) -I$(LINC) -I$(LIBFT)
DEPS = $(patsubst %.o,%.d, $(OBJS))
DEPFLAGS := -MMD -MP
LDFLAGS := -lreadline -L$(LIBFT) -lft
CFLAGS = -Wall -Wextra -Werror $(DEPFLAGS)
CC := cc
MKDIR := mkdir -p
OS = $(shell uname)

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

ft: $(OBJS) | $(ODIR)
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
	pip list --outdated
	pip install -U -r requirements.txt
	norminette $(SRCS)

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
