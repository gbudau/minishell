NAME=minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lft
RMF=rm -rf

INC_DIR = include
SRC_DIR = src
LIB_DIR = libft
OBJ_DIR = obj
UNAME = $(shell uname -s)

_OBJ = main.o
OBJ := $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))

_DEPS = minishell.h libft.h
DEPS := $(patsubst %, $(INC_DIR)/%, $(_DEPS))

.PHONY: all
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I$(INC_DIR) -L$(LIB_DIR) $(LDFLAGS)

.PHONY: fsanitize
fsanitize: CFLAGS += -g3 -O0 -fsanitize=address
fsanitize: fclean $(OBJ)
	make CFLAGS="$(CFLAGS)" -C $(LIB_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I$(INC_DIR) -L$(LIB_DIR) $(LDFLAGS)
	./$(NAME)

.PHONY: debug
debug: CFLAGS += -g3 -O0
debug: fclean $(OBJ)
	make CFLAGS="$(CFLAGS)" -C $(LIB_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I$(INC_DIR) -L$(LIB_DIR) $(LDFLAGS)

ifeq ($(UNAME),Linux)
.PHONY: valgrind
valgrind: fclean debug
	valgrind --leak-check=full ./$(NAME)
endif

ifeq ($(UNAME),Darwin)
.PHONY: leaks
leaks: fclean debug
	DYLD_INSERT_LIBRARIES=/Applications/Xcode.app/Contents/Developer/usr/lib/libLeaksAtExit.dylib leaks -atExit -- ./$(NAME)
endif

.PHONY: clean
clean:
	make -C $(LIB_DIR) fclean
	$(RMF) $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
