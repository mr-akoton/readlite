# ============================================================================ #
# VARIABLES

LIB_NAME	= readlite
LIB_STATIC	= lib$(LIB_NAME).a
LIB_SHARED	= lib$(LIB_NAME).so

TEST_NAME	= rl_test

# ============================================================================ #
# DIRECTORIES

SRC_DIR	= src
INC_DIR	= include
OBJ_DIR	= build

TEST_DIR = test

# ============================================================================ #
# COMPILATOR SETTINGS

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pedantic -O2 -fPIC
CFLAGS += -I $(INC_DIR)
LDFLAGS	= -shared

ifdef DEBUG
	CFLAGS += -g -O0 -DDEBUG
endif

# ============================================================================ #
# SOURCES

SRCS	= $(wildcard $(SRC_DIR)/*.c)
OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_SRCS	= $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS	= $(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# ============================================================================ #
# RULES

# ----- Main Rules ----------------------------------------------------------- #

all: $(LIB_STATIC) $(LIB_SHARED)

test: $(LIB_STATIC) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -L. -l$(LIB_NAME) -o $(TEST_NAME)

# ----- Dependencies --------------------------------------------------------- #

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_STATIC): $(OBJS)
	ar rcs $@ $^
	@echo "Static library create: $(LIB_STATIC)"

$(LIB_SHARED): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Shared library create: $(LIB_SHARED)"

# Test binaries
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# ----- Side Rules ----------------------------------------------------------- #

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIB_STATIC) $(LIB_SHARED) $(TEST_NAME)

re: fclean all

# ============================================================================ #
# PHONY

.PHONY: all clean fclean