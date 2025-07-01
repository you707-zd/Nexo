# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRC = main.c shell.c scheduling.c helper.c

# Object files (replace .c with .o)
OBJ = $(SRC:.c=.o)

# Output executable name
OUT = nexo

# Default target
$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

# How to compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean command to delete object files and executable
clean:
	rm -f *.o $(OUT)
