
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -g

# Source files
SRCS = Compilers.c MainReader.c Reader.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = my_program

# Default target
all: $(EXEC)

# Rule to link object files and create the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean
