# List of object files
OBJS = uimain.o tokenizer.o history.o

# Compiler flags for debugging and optimization
CFLAGS = -g -O3

# The first target is the default target. Usually named "all"
all: uimain

# Build the main executable "uimain" from the object files
uimain: $(OBJS)
	$(CC) -o uimain $(CFLAGS) $(OBJS)

# The object files are dependent on their respective header files
$(OBJS): tokenizer.h history.h

# Clean up object files and the executable
clean:
	rm -f *.o uimain

# Convenience target to run the executable
run: uimain
	./uimain
