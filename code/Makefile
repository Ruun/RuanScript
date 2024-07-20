# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRCS = Compilers.c MainReader.c Reader.c Scanner.c MainScanner.c

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

# Check target to ensure the project builds correctly
check: all
	@echo "Checking if the project compiles without errors..."

# Dist target to simulate creating a distribution package (for example purposes)
dist:
	@echo "Creating distribution package..."
	# Add commands to create a distribution package here

# Distcheck target to run dist and check targets
distcheck: dist check
	@echo "Running distcheck..."
	# Add additional distribution checks here

# Clean up the build
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean check dist distcheck

