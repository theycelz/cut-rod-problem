CC = gcc
CFLAGS = -Wall -Wextra


OBJ = rod_cutting.o main.o
TARGET = rod_cutting

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

rod_cutting.o: rod_cutting.c rod_cutting.h
	$(CC) $(CFLAGS) -c rod_cutting.c

main.o: main.c rod_cutting.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJ) $(TARGET)