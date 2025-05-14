# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude -pthread

# Directories and files
SRC_DIR = src
OBJ_DIR = build
TARGET = crawler

# Source and object files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Default target
.PHONY: all clean dev run

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) -lcurl

# Run: just execute the binary
run:
	@if [ -f ./$(TARGET) ]; then \
		echo "Running $(TARGET)..."; \
		./$(TARGET); \
	else \
		echo "Error: Binary '$(TARGET)' not found. Run 'make' or 'make dev' first."; \
		exit 1; \
	fi

# Dev: build and run
dev: all run

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
