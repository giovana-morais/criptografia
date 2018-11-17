CC 	= gcc
CFLAGS 	= -I -Wall
LDFLAGS	= -lm -lgmp 
DEPS 	= rsa.h
OBJ	= main.o rsa.o
TARGET	= rsa


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(TARGET) *~
