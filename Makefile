NAME		=	libsha.a
MAIN		=	t_main
TEST_BIN	=	test_exec

CC		=	gcc
AR		=	ar rc
CFLAGS		=	-Wall -Wextra
INCLUDES	=	-Iincludes/

SRC_DIR		=	src
TEST_DIR	=	test

LIB_SRC		=	$(shell find $(SRC_DIR) -name '*.c' ! -name 'main.c')
LIB_OBJ		=	$(LIB_SRC:.c=.o)

TEST_SRC	=	$(TEST_DIR)/test.c
TEST_OBJ	=	$(TEST_SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB_OBJ)
	$(AR) $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

t_main: $(NAME)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(SRC_DIR)/main.c -L. -lsha -lm

test: $(TEST_OBJ) $(NAME)
	$(CC) $(INCLUDES) -o $(TEST_BIN) $< -L. -lsha -lcriterion -lm

tests_run: test
	./$(TEST_BIN)

clean:
	$(RM) $(LIB_OBJ) $(TEST_OBJ)

fclean: clean
	$(RM) $(NAME) $(MAIN) $(TEST_BIN)

re: fclean all

.PHONY: all clean fclean re t_main test tests_run
