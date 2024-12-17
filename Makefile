CC = gcc
CFLAGS = -Wall -g
OBJ = Creature.o Game.o Item.o Player.o Room.o
TARGET = Game.exe

# Build target
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Convert .c files to .o files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target (Windows compatible)
clean:
	del /f /q $(OBJ) $(TARGET)

# Rebuild (clean and rebuild)
rebuild: clean $(TARGET)
