CC 	= gcc
CFLAGS 	= -I -Wall
LDFLAGS	= -lm -lgmp 
OBJ	= main.o 
TARGET	= rsa


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(TARGET) *~
