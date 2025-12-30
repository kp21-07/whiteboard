CC = gcc
CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = src/protocol.c src/canvas.c src/drawing.c src/main.c 
OBJ = $(SRC:.c=.o)
TARGET = whiteboard

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) -MMD -MP

-include src/*.d

clean:
	rm -f src/*.o $(TARGET)
