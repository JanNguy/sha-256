NAME_LIB    = libcrypto.a
SRC_LIB     = src
LIB_ITEMS   = add32.c and32.c bigSigma0.c bigSigma1.c ch32.c const_adress.c \
              isPrime.c maj32.c not32.c or32.c rotl32.c rotr32.c shr32.c \
              SmallSigma0.c SmallSigma1.c xor32.c
SRC_TEST    = test
SRC_ITEMS   = test.c
CC          = gcc
AR          = ar rc
# CFLAGS      = -Wall -Wextra -Werror
INCLUDES	=	includes/

LIB_OBJS    = $(LIB_ITEMS:.c=.o)
TEST_OBJS   = $(SRC_ITEMS:.c=.o)
TARGET      = test_exec

.PHONY: all lib test tests_run clean fclean re

all: lib test

tests_run: test
	./$(TARGET)

lib: $(addprefix $(SRC_LIB)/,$(LIB_OBJS))
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
