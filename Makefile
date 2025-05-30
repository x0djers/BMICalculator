CC = gcc

INCLUDE_DIRS = -Ibackend/vendor/json \
 			   -Ibackend/vendor/mongoose \
 			   -Ibackend/vendor/logger \
 			   -Ibackend

FLAGS = -Wall -Wextra -g -DDEBUG $(INCLUDE_DIRS)

SRC_DIR = ./backend
BUILD_DIR = ./build
BIN_DIR = ./bin
BUILD_SRC_DIR = $(BUILD_DIR)/backend

LIB_SRC := $(shell find $(SRC_DIR) -type f -name "*.c" ! -name "main.c")
MAIN_SRC := $(SRC_DIR)/main.c

LIB_OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_SRC_DIR)/%.o,$(LIB_SRC))
MAIN_OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_SRC_DIR)/%.o,$(MAIN_SRC))
ALL_OBJ := $(LIB_OBJ) $(MAIN_OBJ)

TARGET = $(BIN_DIR)/server

all: create-dirs $(TARGET)

rebuild: clean all

create-dirs:
	mkdir -p $(BIN_DIR) $(dir $(ALL_OBJ))

$(BUILD_SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(ALL_OBJ)
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all rebuild clean
