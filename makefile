### Makefile for building swoon ###

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/swoon
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC = clang
CFLAGS = -std=c99 -Wall -g
LDLIBS = -F/System/Library/PrivateFrameworks -framework Carbon -framework SkyLight

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR) $(BIN_DIR)
