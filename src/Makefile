# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Object files
OBJ = uimain.o

# Executable name
EXEC = uimain

# Default target
all: $(EXEC)

# Build the main executable
$(EXEC): uimain.o
	$(CC) $(CFLAGS) uimain.o -o $(EXEC)

# Compile uimain.c
uimain.o: uimain.c tokenizer.h history.h
	$(CC) $(CFLAGS) -c uimain.c

# Clean target to remove generated files
clean:
	rm -f $(OBJ) $(EXEC)
