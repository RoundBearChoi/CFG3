# ================================================
# Simple raylib Makefile for Linux (C Fighting Game 3)
# ================================================

CC       = gcc
CFLAGS   = -Wall -Wextra -std=c11 -O2 -D_DEFAULT_SOURCE
TARGET   = CFG3

# Source files (easy to expand later)
SRC      = src/main.c

# Raylib linking flags — works on almost every Linux/WSL setup
LIBS := $(shell pkg-config --libs raylib 2>/dev/null || echo "-lraylib -lGL -lm -lpthread -ldl -lrt -lX11")

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
