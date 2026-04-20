NAME_LIB    = libcrypto.a
SRC_LIB     = src
SRC_TEST    = test
SRC_ITEMS   = test.c
CC          = gcc
AR          = ar rc
# CFLAGS      = -Wall -Wextra -Werror
INCLUDES	=	includes/

LIB_OBJS    = $(shell find $(SRC_LIB) -name '*.c' | sed 's|\.c$|.o|')
TEST_OBJS   = $(SRC_ITEMS:.c=.o)
TARGET      = test_exec

.PHONY: all lib test tests_run clean fclean re

all: lib test

tests_run: test
	./$(TARGET)

lib: $(LIB_OBJS)
	$(AR) $(NAME_LIB) $^

$(SRC_LIB)/%.o: $(SRC_LIB)/%.c
	$(CC) -c $< -o $@ -I$(INCLUDES)

test: $(SRC_TEST)/$(TEST_OBJS) lib
	$(CC) -o $(TARGET) $< -L. -lcrypto -I$(INCLUDES) -lcriterion -lm

$(SRC_TEST)/%.o: $(SRC_TEST)/%.c
	$(CC) -c $< -o $@ -I$(INCLUDES)

clean:
	rm -f $(SRC_LIB)/*.o $(SRC_TEST)/*.o

fclean: clean
	rm -f $(NAME_LIB) $(TARGET)

re: fclean all
