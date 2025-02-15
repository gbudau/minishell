NAME = minishell
LIBFT = libft.a

CC = gcc
DEBUGGER = lldb
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lft
RMF=rm -rf

INC_DIR = include
SRC_DIR = src
LIB_DIR = libft
OBJ_DIR = obj

LIBS = $(LIB_DIR)/$(LIBFT)

UNAME = $(shell uname -s)

_OBJ = main.o

# Signal handling
_OBJ += signal_handlers.o \
		signal_handlers_utils.o

# Environment variables
_OBJ += env.o \
		env_utils.o \
		env_utils2.o


# Parser
_OBJ += parser.o \
		parser_utils.o \
		parser_utils2.o

# Lexer
_OBJ += lexer.o \
		lexer_word_token.o \
		lexer_word_utils.o \
		lexer_utils1.o \
		lexer_utils2.o

# Words Expansion
_OBJ += word_exp.o \
		word_exp_utils.o \
		quote_removal.o \
		word_exp_io.o \
		word_exp_argv.o

# Pipeline
_OBJ += pipeline.o \
		pipeline_utils.o

# Input/Output redirection
_OBJ += io_redirection.o

# Builtins
_OBJ += builtins.o \
		msh_echo.o \
		msh_exit.o \
		msh_pwd.o \
		msh_env.o \
		msh_unset.o \
		msh_export.o \
		msh_cd.o \

# Execute command
_OBJ += execute_cmd.o \
		execute_cmd_utils.o \
		execute_cmd_utils2.o

# Set SHLVL
_OBJ += set_shlvl.o

# Clear lists functions
_OBJ += clear.o

# Error functions
_OBJ += error_utils.o

# Misc
_OBJ += atoll_error.o

OBJ := $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))

_DEPS = minishell.h \
		libft.h \
		signalhandlers.h \
		command.h \
		env.h \
		lexer.h \
		parser.h \
		wordexp.h \
		pipeline.h \
		ioredirection.h \
		builtins.h \
		clear.h \
		errors.h \
		execute.h

DEPS := $(patsubst %, $(INC_DIR)/%, $(_DEPS))

.PHONY: all
all: make_library $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

.PHONY: make_library
make_library:
	make -C $(LIB_DIR)

$(LIB_DIR)/$(LIBFT):
	make -C $(LIB_DIR)

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I$(INC_DIR) -L$(LIB_DIR) $(LDFLAGS)

.PHONY: fsanitize
fsanitize: CFLAGS += -fsanitize=address
fsanitize: debuginfo
	ASAN_OPTIONS=detect_leaks=1 ./$(NAME)

.PHONY: debuginfo
debuginfo: CFLAGS += -g3
debuginfo: fclean $(OBJ)
	make CFLAGS="$(CFLAGS)" -C $(LIB_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I$(INC_DIR) -L$(LIB_DIR) $(LDFLAGS)

.PHONY: debug
debug: debuginfo
	$(DEBUGGER) ./$(NAME)

.PHONY: leaks
leaks: debuginfo
ifeq ($(UNAME),Linux)
	valgrind --leak-check=full --track-fds=yes ./$(NAME)
else
ifeq ($(UNAME),Darwin)
	DYLD_INSERT_LIBRARIES=/Applications/Xcode.app/Contents/Developer/usr/lib/libLeaksAtExit.dylib leaks -atExit -- ./$(NAME)
endif	
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
