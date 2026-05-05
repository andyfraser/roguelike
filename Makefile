CC = cc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = -lncurses

SRC = src/main.c src/map.c src/monster.c src/skills.c src/item.c src/monster_data.c
OBJ = $(SRC:src/%.c=obj/%.o)
TARGET = roguelike

TEST_SRC = tests/unit_tests.c src/map.c src/monster.c src/skills.c src/item.c src/monster_data.c
TEST_OBJ = obj/unit_tests.o obj/map.o obj/monster.o obj/skills.o obj/item.o obj/monster_data.o
TEST_TARGET = unit_tests

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/unit_tests.o: tests/unit_tests.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(TEST_OBJ) -o $(TEST_TARGET) $(LDFLAGS)

clean:
	rm -rf obj $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
