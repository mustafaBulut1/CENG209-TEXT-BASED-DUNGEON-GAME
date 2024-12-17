CC = gcc
CFLAGS = -Wall -g
OBJ = Creature.o Game.o Item.o Player.o Room.o
TARGET = Game.exe

# Derleme hedefi
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# .c dosyalarını .o dosyalarına çevir
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Temizleme hedefi (Windows uyumlu)
clean:
	del /f /q $(OBJ) $(TARGET)

# Rebuild (temizle ve yeniden derle)
rebuild: clean $(TARGET)
