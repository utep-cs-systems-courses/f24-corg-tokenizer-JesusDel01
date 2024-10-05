# List of object files
OBJS = uimain.o tokenizer.o

# Build the main executable "uimain" from the object files
uimain: $(OBJS)
	$(CC) -o uimain $(CFLAGS) $(OBJS)

# Build individual oject files
uimain.o: uimain.c tokenizer.h
	$(CC) $(CFLAGS) -c uimain.c

tokenizer.o: tokenizer.c tokenizer.h
	$(CC) $(CFLAGS) -c tokenizer.c

# clean target to delete the generated files
clean:
	rm -f *.o uimain

#convenience to run th uimian executable
run: uimain
	./uimain
