# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Paths
MODULES = ./modules
INCLUDE = ./include
ADTs = ./ADTs

# Automatically find all .c files and convert them to .o
MODULES_SRC = $(wildcard $(MODULES)/*.c)
ADTS_SRC = $(wildcard $(ADTs)/*.c)
OBJ = $(patsubst %.c,%.o,$(MODULES_SRC) $(ADTS_SRC))

# Print the object files being compiled for debugging
$(info Object files to compile: $(OBJ))

# Executable program
EXEC = out

# Default rule
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ) -lm  # Add -lm here

# Compile .c files from MODULES and ADTs directories into .o files
$(MODULES)/%.o: $(MODULES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ADTs)/%.o: $(ADTs)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the executable
run: all
	./$(EXEC) -i init.txt

# Clean the build directory
clean:
	rm -f $(OBJ) $(EXEC)
	clear
