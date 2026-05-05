# ================================================
# Makefile for C Fighting Game 3 (raylib)
# ================================================

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2 -D_DEFAULT_SOURCE
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Add every .c file here as you create new modules
SOURCES = src/main.c \
          src/rbg_render_debug/rbg_render_debug.c

TARGET = CFG3

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(LDFLAGS)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET)

.PHONY: all run clean
