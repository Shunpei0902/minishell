NAME := minishell

SDIR := src/
ODIR := obj/
IDIR := inc/
LDIR = $(RLDIR)/lib
LINC = $(RLDIR)/include
SRCS := $(SDIR)/*.c
OBJS := $(SRCS:%.c=$(ODIR)%.o)
INCS = -I$(IDIR) -I$(LINC)
DEPS = $(patsubst %.o,%.d, $(OBJS))
DEPFLAGS := -MMD -MP
LDFLAGS := -lhistory -lreadline
RLDIR =`brew --prefix readline`
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
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

all: $(NAME) $(LIBFT_LIB)

$(NAME): $(SRCS) $(LIBFT_LIB)
	$(CC)  $(CFLAGS) -o $(NAME) $(LIBFT_LIB) $^ $(INCS) -L$(LDIR) $(LDFLAGS) 

# $(NAME): $(OBJS) | $(ODIR)
# 	$(CC)  $(CFLAGS) -o $(NAME) $^ -L$(LDIR) $(LDFLAGS)

$(ODIR)%.o:$(SDIR)%.c | $(ODIR)
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LDFLAGS)

$(ODIR):
	@echo "Creating directory: $(ODIR)"
	$(MKDIR) $@

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

clean:
	rm -rf $(ODIR)

fclean: clean
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
