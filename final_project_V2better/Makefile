CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = stegoapp
OBJECTS = main.o stego.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.c stego.h
	$(CC) $(CFLAGS) -c main.c

stego.o: stego.c stego.h
	$(CC) $(CFLAGS) -c stego.c

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
