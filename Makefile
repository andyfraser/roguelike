CC = cc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lncurses

SRC = main.c map.c monster.c skills.c item.c
OBJ = $(SRC:.c=.o)
TARGET = roguelike

TEST_SRC = tests/unit_tests.c map.c monster.c skills.c item.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = unit_tests

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(TEST_OBJ) -o $(TEST_TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET) $(TEST_TARGET) tests/*.o

.PHONY: all clean test
