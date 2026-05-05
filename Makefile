# ================================================
# Makefile for C Fighting Game 3 (raylib)
# ================================================

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2 -D_DEFAULT_SOURCE
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Automatically find ALL .c files recursively under src/
SRCDIR   = src
SOURCES := $(shell find $(SRCDIR) -type f -name '*.c')

# Convert source paths to object paths (preserves directory structure)
OBJECTS := $(SOURCES:.c=.o)

TARGET = CFG3

# Default target
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# Compile each source file to an object file
%.o: %.c
	@mkdir -p $(dir $@)          # create subdirectories if they don't exist yet
	$(CC) $(CFLAGS) -c $< -o $@

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all run clean
