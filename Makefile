# ================================================
# Makefile for C Fighting Game 3 (raylib) - Out-of-source build
# ================================================
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2 -D_DEFAULT_SOURCE
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# ========================= CONFIGURATION =========================
SRCDIR   = src
BUILDDIR = build
TARGET   = CFG3
# ================================================================

# Automatically find all .c files recursively
SOURCES := $(shell find $(SRCDIR) -type f -name '*.c')

# Transform src/xxx/yyy.c → build/xxx/yyy.o
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

# Final executable path
EXECUTABLE = $(BUILDDIR)/$(TARGET)

# Default target
all: $(EXECUTABLE)

# Link the final executable
$(EXECUTABLE): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# Compile each source to object (creates subdirs automatically)
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Run the game (from build folder)
run: $(EXECUTABLE)
	@echo "Running $(TARGET)..."
	@./$(EXECUTABLE)

# Clean everything
clean:
	rm -rf $(BUILDDIR)

.PHONY: all run clean
