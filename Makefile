# ============================================================================ #
# VARIABLES

LIB_NAME	= readlite
LIB_STATIC	= lib$(LIB_NAME).a
LIB_SHARED	= lib$(LIB_NAME).so
TEST_NAME	= rl_test

# ============================================================================ #
# DIRECTORIES

SRC_DIR		= src
INC_DIR		= include
OBJ_DIR		= build
TEST_DIR	= test

# ============================================================================ #
# COMPILER SETTINGS

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pedantic -O2 -fPIC -std=gnu2x
CFLAGS		+= -I $(INC_DIR)
LDFLAGS		= -shared

ifdef DEBUG
	CFLAGS	+= -g -O0 -DDEBUG
endif

# ============================================================================ #
# SOURCES

SRCS		= readlite.c \
			  display/cursor.c \
			  display/render.c \
			  input/buffer.c \
			  input/input.c \
			  input/signal.c \
			  terminal/term_mode.c \
			  terminal/term.c \
			  util/iomanip.c \
			  util/string.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

TEST_SRCS	= main.c
TEST_OBJS	= $(addprefix $(OBJ_DIR)/, $(TEST_SRCS:.c=.o))

# ============================================================================ #
# RULES

# ----- Main Rules ----------------------------------------------------------- #

all: $(LIB_STATIC) $(LIB_SHARED)

test: fclean $(LIB_STATIC) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -L. -l$(LIB_NAME) -lreadline -o $(TEST_NAME)

# ----- Build Rules ---------------------------------------------------------- #

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_STATIC): $(OBJS)
	@ar rcs $@ $^
	@echo "✅ Static library created: $@"

$(LIB_SHARED): $(OBJS)
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo "✅ Shared library created: $@"

# ----- Cleanup -------------------------------------------------------------- #

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIB_STATIC) $(LIB_SHARED) $(TEST_NAME)

re: fclean all

# ============================================================================ #
# PHONY

.PHONY: all clean fclean re test
